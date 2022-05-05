
open Hidden_Words_TR

(* Hidden Words with List-based Sets. *)
module Hidden_Words_List_Set = HiddenWords_TR_F ( ListSet.ListSetM )

module HW_Tests_for_List_Set = 
  Tests_for_Hidden_Words.Hidden_Tests ( Hidden_Words_List_Set )

let () = 
  print_endline 
    "\nRunning Hidden Words TR tests for list-based sets: ListSetM.\n";
  HW_Tests_for_List_Set.run ()


(* Hidden Words with Binary Search Tree-based Sets. *)
module Hidden_Words_BSTree_Set = HiddenWords_TR_F ( BSTree.BSTreeSetM )

module HW_Tests_for_BSTree_Set = 
  Tests_for_Hidden_Words.Hidden_Tests ( Hidden_Words_BSTree_Set )

let () = 
  print_endline 
    "\nRunning Hidden Words TR tests for binary search tree-based sets: BSTreeSetM.\n";
  HW_Tests_for_BSTree_Set.run ()


(* Hidden Words with Red Black Tree-based Sets. *)

module Hidden_Words_RBTree_Set = HiddenWords_TR_F ( RBTree.RBTreeSetM )

module HW_Tests_for_RBTree_Set = 
  Tests_for_Hidden_Words.Hidden_Tests ( Hidden_Words_RBTree_Set )

let () = 
  print_endline 
    "\nRunning Hidden Words tests for red-black tree-based sets: RBTreeSetM.\n";
  HW_Tests_for_RBTree_Set.run ()

