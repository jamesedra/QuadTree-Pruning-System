# Memo-ized Binary Tree for Image Processing and Compression

# Project Overview

This repository contains my solution to Programming Assignment 3 (PA3) for UBC CPSC 221. The assignment focuses on constructing memoized structures, implementing binary trees for image data storage, designing complex recursive algorithms, and exploring image compression using space-partitioning trees.

The assignment is divided into two parts:

- Implementing the ImgTree class: The ImgTree class represents a binary tree where each node represents a rectangular region of a PNG image. The tree is constructed by dividing regions based on minimizing color variation. Various functions, including constructing the tree, computing average colors and entropy, and rendering the image, have been implemented.
- Image compression using ImgTrees: This part involves using the hierarchical structure of the tree and the average color information to prune regions of the image with low color variability. This reduces the size of the data structure while preserving fine pixel-level details.

# Project Structure

The project consists of the following files:

    stats_private.h: Header file containing private declarations for the Stats class.
    stats.cpp: Implementation file for the Stats class, which provides functions to compute average color and entropy for rectangular image regions.
    imgtree_private.h: Header file containing private declarations for the ImgTree class.
    imgtree.cpp: Implementation file for the ImgTree class, including functions to construct the tree, manipulate the tree structure, and perform image rendering and compression.
    main.cpp: File containing basic tests for the ImgTree class.
    testComp.cpp: File containing additional tests for image compression using ImgTrees.

# Examples

Original image source (left) and a rendered image after pruning at a specific tolerance (right):

<img src="https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/99d0e56a-1fa7-4231-aded-e76e263109f5" width="340"> <img src="https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/a65a9f2e-14a4-4889-99d1-15d098961d34" width="340">


Original image (left) and and a rendered image after flipping horizontally with only using 
binary tree manipulation (right):

![fnr-354x200](https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/539dc98c-5521-4f0e-b77a-34a2e3d0cf11) ![fnr-flip](https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/30288cd4-ca33-476b-9685-19b386eb7779)

Original image (left) and a rendered image both pruned at a specific tolerance, and flipped using
binary tree manipulation (right):

![kkkk-kmnn-480x270](https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/33efcb1e-f16f-4632-8e84-fba5fb438d96) ![kkkk-prune01-flip](https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/c67993a9-12da-4fe3-887e-8fbbd449f60a)


An animated GIF to show the first 20 partitions of the ImgTree constructing the image based on
average color values:

![kkkk-kmnn-20levels](https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/9cc6d195-0721-4938-9525-65d45685a96b)

