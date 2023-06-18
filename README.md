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

Original image source (left) and a rendered image after pruning at a tolerance 0.5:

<img src="https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/3f7f3e17-b902-46e8-b3e3-de76c0195c45" width="340"> <img src="https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/dc23a478-7e91-43f3-b41f-5011610b0a20" width="340">

Original image (left) and a rendered image after flipping horizontally with only using 
binary tree manipulation (right):

<img src="https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/2091f24e-f65c-42b0-8ecf-c417c4eb336e" width="340"> <img src="https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/51da3289-1e37-4ed2-a0fa-b409f9f6022f" width="340">

Original image (left) and a rendered image both pruned at a specific tolerance, and flipped using
binary tree manipulation (right):

<img src="https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/7692e3bb-c8d3-4c4e-99b4-5711f761a649" width="340">
<img src="https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/e62d6041-3070-4dbf-ac97-e0d62efac61f" width="340">

An animated GIF to show the first 20 partitions of the ImgTree constructing the image based on
average color values:

![kkkk-kmnn-20levels](https://github.com/jamesedra/Memo-ized-Binary-Tree-for-Image-Processing-and-Compression-/assets/107374254/87a8756f-89d9-412f-9ade-dee87f2b93f4)


