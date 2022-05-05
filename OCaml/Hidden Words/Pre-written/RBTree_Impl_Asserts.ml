(* Some simple `assert` style tests that you may modify and extend to
   test functions in the `RBTreeS` signature but also helper functions
   exposed using the `RBTreeImplS` signature.

   You can compile and run this file as follows:
     ocamlbuild RBTree_Impl_Asserts.byte
     ./RBTree_Impl_Asserts.byte

   Or you can load it into utop as follows:
     utop
     # mod_use "SetSig.ml" ;;
     # mod_use "BSTreeSig.ml" ;;
     # mod_use "RBTreeSig.ml" ;;
     # mod_use "RBTree.ml" ;;
     # use "RBTree_Impl_Asserts.ml" ;;

  *)

open RBTree
open RBTreeImplM

(* This is a balanced tree since 2 is inserted first. The 1 goes
   into the left sub-tree and 3 into the right one.
 *)
let t1 : int t = List.fold_right insert [3;1;2] empty
let height_t1 = height t1
let size_t1 = size t1

let () = 
  assert (height_t1 = 2);
  assert (size_t1 = 3)

(* This is an unbalanced tree since 3 is inserted first. The both
   2 and then 1 go into the left sub-tree.
 *)
let t2 : int t = List.fold_right insert [1;2;3] empty
let height_t2 = height t2
let size_t2 = size t2

let () = 
  assert (height_t2 = 2);
  assert (size_t2 = 3)

(* We see the imbalance more dramatically with larger tree. But
   the same principles apply.
 *)
let t3 : int t = List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty
let height_t3 = height t3
let size_t3 = size t3

let () = 
  assert (height_t3 <= 5);
  assert (size_t3 = 10)

let t4 : int t = List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty
let height_t4 = height t4
let size_t4 = size t4

let () = 
  assert (height_t4 <= 5);
  assert (size_t4 = 10)

(* Some tests similar to the property for problem 7 in Hwk 05. *)
let () =
  assert (elem 4  (insert  4 t1));
  assert (elem 4  (insert  4 t2));
  assert (elem 4  (insert  4 t3));
  assert (elem 4  (insert  4 t4));
  assert (elem 29 (insert 29 t3));
  assert (elem 29 (insert 29 t4));
  assert (not (elem 39 (insert 29 t4)))

(* Verify that all 4 trees are binary search trees. *)
let () = 
  assert (is_bst t1);
  assert (is_bst t3);
  assert (is_bst t3);
  assert (is_bst t4)

(* Check that an out-of-order tree is not a binary search tree. *)
let out_of_order = 
  T (B, E, 9, T ( B, T (B, E ,8, E), 10 , T (B, E, 11, E) ))

let () =
  assert (not (is_bst out_of_order))


(* Below you may add some extra tests, perhaps some for your helper
   functions from `RBTreeImplS`.
 *)





(* Check that some trees are not red-black trees. *)
let not_rbtree_1 = T (R, T (R, E, 1, E), 2, T (B, E, 3, E))
let not_rbtree_2 = T (R, T (B, E, 1, E), 2, T (R, E, 3, E))

let () =
  assert (not (is_red_black_tree not_rbtree_1));
  assert (not (is_red_black_tree not_rbtree_2))



(* Below you may add some extra tests, perhaps some for your helper
   functions from `RBTreeImplS`.
 *)

