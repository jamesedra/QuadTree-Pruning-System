/**
 * @file imgtree_private.h
 * @description student declarations of private functions
 *              for ImgTree, CPSC 221 2023S PA3
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below
pair<pair<pair<unsigned int, unsigned int>, pair<unsigned int, unsigned int>>, pair<pair<unsigned int, unsigned int>, pair<unsigned int, unsigned int>>> SplitPos(Stats& s, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr);
void RenderHelper(Node* node, PNG& image) const;
void ClearHelper(Node* node);
Node* CopyHelper(const Node* node);
vector<HSLAPixel> PruneHelper(Node* node, double tol);
void FlipHorizontalHelper(Node* node, int offset);

