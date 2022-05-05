#!/bin/bash

ocamlbuild -clean

ocamlbuild time_HW_Lists_Sorted_Words.byte 
time ./time_HW_Lists_Sorted_Words.byte 

ocamlbuild time_HW_Lists_Unsorted_Words.byte 
time ./time_HW_Lists_Unsorted_Words.byte 

ocamlbuild time_HW_BSTree_Sorted_Words.byte 
time ./time_HW_BSTree_Sorted_Words.byte 

ocamlbuild time_HW_BSTree_Unsorted_Words.byte 
time ./time_HW_BSTree_Unsorted_Words.byte 

ocamlbuild time_HW_RBTree_Sorted_Words.byte 
time ./time_HW_RBTree_Sorted_Words.byte 

ocamlbuild time_HW_RBTree_Unsorted_Words.byte 
time ./time_HW_RBTree_Unsorted_Words.byte 

ocamlbuild time_HW_TR_Lists_Sorted.byte 
time ./time_HW_TR_Lists_Sorted.byte 

ocamlbuild time_HW_TR_Lists_Unsorted.byte 
time ./time_HW_TR_Lists_Unsorted.byte 

ocamlbuild time_HW_TR_BSTree_Sorted.byte 
time ./time_HW_TR_BSTree_Sorted.byte 

ocamlbuild time_HW_TR_BSTree_Unsorted.byte
time ./time_HW_TR_BSTree_Unsorted.byte

ocamlbuild time_HW_TR_RBTree_Sorted.byte
time ./time_HW_TR_RBTree_Sorted.byte

ocamlbuild time_HW_TR_RBTree_Unsorted.byte
time ./time_HW_TR_RBTree_Unsorted.byte
