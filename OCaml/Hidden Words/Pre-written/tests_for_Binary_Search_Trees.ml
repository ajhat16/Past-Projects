open Tests
open BSTreeSig

(* The tests here are for elements in `BSTreeS` signature 
   or the `SetS` signature.

   Thus they test `height`, `size`, and `is_bst` but only for trees 
   constructed using `empty` and `insert`. We can only construct 
   trees using the interface functions, not the constructors directly. 
   Tests for these kinds of trees are in `tests_for_BSTreeImpl.ml`.
 *)

module BSTree_Tests (T: BSTreeS) = struct

  open T

  let some_tests = [

    (* some height tests *)
    eval_test (fun () ->
        height (List.fold_right insert [3;1;2] empty), 2)
       "height (List.fold_right insert [3;1;2] empty)"
        Int.to_string;

    eval_test (fun () ->
        height (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty) <= 5, true)
       "height (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty) <= 5"
        Bool.to_string;

    (* some size tests *)
    eval_test (fun () ->
        size (List.fold_right insert [3;1;2] empty), 3)
       "size (List.fold_right insert [3;1;2] empty)"
        Int.to_string;

    eval_test (fun () ->
        size (List.fold_right insert [3;2;1] empty), 3)
       "size (List.fold_right insert [3;2;1] empty)"
        Int.to_string;

    eval_test (fun () ->
        size (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty), 10)
       "size (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty)"
        Int.to_string;

    eval_test (fun () ->
        size (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty), 10)
       "size (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty)"
        Int.to_string;

    (* some is_bst tests *)
    eval_test (fun () ->
        is_bst (List.fold_right insert [3;1;2] empty), true)
       "is_bst (List.fold_right insert [3;1;2] empty)"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (List.fold_right insert [3;2;1] empty), true)
       "is_bst (List.fold_right insert [3;2;1] empty)"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty), true)
       "is_bst (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty)"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty), true)
       "is_bst (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty)"
        Bool.to_string;
    ]

  let run () = run_tests some_tests

end
