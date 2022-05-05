open Tests
open RBTreeSig

(* The tests here are for elements in `RBTreeS` signature that are
   not part of the `BSTreeS` signature or the `SetS` signature.

   Thus they test `is_red_black_tree` but only for trees constructed
   using `empty` and `insert`.  We can only construct trees using the
   interface functions, not the constructors directly. Tests for these
   kinds of trees are in `tests_for_RBTreeImpl.ml`.
 *)

module RBTree_Tests (T: RBTreeS) = struct

  open T

  let some_tests = [
    eval_test (fun () ->
        is_red_black_tree empty, true)
       "is_red_black_tree empty"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (List.fold_right insert [3;1;2] empty), true)
       "is_red_black_tree (List.fold_right insert [3;1;2] empty)"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (List.fold_right insert [1;2;3] empty), true)
       "is_red_black_tree (List.fold_right insert [1;2;3] empty)"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty), true)
       "is_red_black_tree (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty)"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty), true)
       "is_red_black_tree (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty)"
        Bool.to_string;
    ]
                 
  let run () = run_tests some_tests

end
