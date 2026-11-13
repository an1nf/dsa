#include <stdlib.h>

typedef struct Node {
  size_t freq;
  unsigned char ch;
  struct Node *left, *right;
} Node;

static void siftDown(Node **h, size_t n, size_t i) {
  for (;;) {
    size_t l = 2 * i + 1, r = l + 1, m = i;
    if (l < n && h[l]->freq < h[m]->freq) m = l;
    if (r < n && h[r]->freq < h[m]->freq) m = r;
    if (m == i) return;
    Node *t = h[i]; h[i] = h[m]; h[m] = t;
    i = m;
  }
}

static void siftUp(Node **h, size_t i) {
  for (; i > 0 && h[(i - 1) / 2]->freq > h[i]->freq; i = (i - 1) / 2) {
    Node *t = h[i]; h[i] = h[(i - 1) / 2]; h[(i - 1) / 2] = t;
  }
}

static Node *extractMin(Node **h, size_t *n) {
  Node *min = h[0];
  h[0] = h[--*n];
  siftDown(h, *n, 0);
  return min;
}

static Node *newNode(size_t freq, unsigned char ch, Node *left, Node *right) {
  Node *z = malloc(sizeof *z);
  *z = (Node){freq, ch, left, right};
  return z;
}

Node *huffman(const size_t freq[256]) {
  Node *h[256];
  size_t n = 0;
  for (int c = 0; c < 256; c++)
    if (freq[c]) h[n++] = newNode(freq[c], (unsigned char)c, NULL, NULL);
  if (n == 0) return NULL;
  for (size_t i = n / 2; i--; ) siftDown(h, n, i);
  while (n > 1) {
    Node *x = extractMin(h, &n), *y = extractMin(h, &n);
    h[n] = newNode(x->freq + y->freq, 0, x, y);
    siftUp(h, n++);
  }
  return h[0];
}

void huffmanCodes(const Node *z, char *prefix, size_t depth, char codes[256][256]) {
  if (!z->left) {
    if (depth == 0) prefix[depth++] = '0';
    prefix[depth] = '\0';
    for (size_t i = 0; i <= depth; i++) codes[z->ch][i] = prefix[i];
    return;
  }
  prefix[depth] = '0';
  huffmanCodes(z->left, prefix, depth + 1, codes);
  prefix[depth] = '1';
  huffmanCodes(z->right, prefix, depth + 1, codes);
}

void freeHuffman(Node *z) {
  if (!z) return;
  freeHuffman(z->left);
  freeHuffman(z->right);
  free(z);
}
