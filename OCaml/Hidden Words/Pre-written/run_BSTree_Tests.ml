
open BSTree

(* Set Tests *)
module BSTree_Set_Tests = 
  Tests_for_Sets.Set_Tests (BSTreeSetM)

let () = 
  print_endline 
    "\nRunning set signature tests for BSTree.\n";
  BSTree_Set_Tests.run ()


(* Binary Search Tree Tests *)
module BSTree_BST_Tests = 
  Tests_for_Binary_Search_Trees.BSTree_Tests (BSTreeM)

let () = 
  print_endline 
    "\nRunning binary search tree signature tests for BSTree.\n";
  BSTree_BST_Tests.run ()


(* Implmenentation tests *)
module BSTree_Impl_Tests = 
  Tests_for_BSTreeImpl.BSTree_Tests (BSTreeImplM)

let () = 
  print_endline 
    "\nRunning implementation tests for BSTree.\n";
  BSTree_Impl_Tests.run ()
