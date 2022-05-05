
open RBTree

(* Set Tests *)
module RBTree_Set_Tests =
  Tests_for_Sets.Set_Tests (RBTreeSetM)

let () = 
  print_endline
    "\nRunning set signature tests for RBTree.\n";
  RBTree_Set_Tests.run ()


(* Binary Search Tree Tests *)
module RBTree_BST_Tests = 
  Tests_for_Binary_Search_Trees.BSTree_Tests (RBTreeBSTM)

let () = 
  print_endline
    "\nRunning binary search tree signature tests for RBTree.\n";
  RBTree_BST_Tests.run ()


(* Red-Black Tree Tests *)
module RBTree_RBT_Tests = 
  Tests_for_Red_Black_Trees.RBTree_Tests (RBTreeImplM)

let () = 
  print_endline
    "\nRunning red-black tree signature tests for RBTree.\n";
  RBTree_RBT_Tests.run ()


(* Implmenentation tests *)
module RBTree_Impl_Tests = 
  Tests_for_RBTreeImpl.RBTree_Tests (RBTreeImplM)

let () = 
  print_endline 
    "\nRunning implementation tests for RBTree.\n";
  RBTree_Impl_Tests.run ()
