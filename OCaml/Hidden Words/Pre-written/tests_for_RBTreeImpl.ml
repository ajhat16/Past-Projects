open Tests
open RBTree

(* The tests here are for the `RBTreeImplM` implementation. The tests
   thus have access to all elements of the `RBTreeImplS` signature.
 
   Importantly, this includes the tree constructors `E` and `T` that
   are not accessible to tests limited in their view by the `RBTreeS`
   signature.

   Having access to these constructors allows us to create trees directly
   instead of via `empty` and `insert` and then to test our `height`, 
   `size`, `is_bst`, and `is_red_black_tree` functions.
 *)

module RBTree_Tests (T: RBTreeImplS) = struct

  open T

  let some_tests =   [

    (* some height tests *)
    eval_test (fun () ->
        height E, 0)
       "height E"
        Int.to_string;

    eval_test (fun () ->
        height (T (B, E, 1, E)), 1)
       "height (T (B, E, 1, E))"
        Int.to_string;

    eval_test (fun () ->
        height (T (B, T (B, E, 1, E), 1, E)), 2)
       "height (T (B, T (B, E, 1, E), 1, E))"
        Int.to_string;

    eval_test (fun () ->
        height (T (B, T (B, E, 1, E), 1, T (B, E, 1, E))), 2)
       "height (T (B, T (B, E, 1, E), 1, T (B, E, 1, E)))"
        Int.to_string;

    eval_test (fun () ->
        height (List.fold_right insert [3;2;1] empty), 2)
       "height (List.fold_right insert [3;2;1] empty)"
        Int.to_string;

    eval_test (fun () ->
        height (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty) <= 5, true)
       "height (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty) <= 5"
        Bool.to_string;

    (* some size tests *)
    eval_test (fun () ->
        size E, 0)
       "size E"
        Int.to_string;

    eval_test (fun () ->
        size (T (B, E, 1, E)), 1)
       "size (T (B, E, 1, E))"
        Int.to_string;

    eval_test (fun () ->
        size (T (B, T (B, E, 1, E), 1, E)), 2)
       "size (T (B, T (B, E, 1, E), 1, E))"
        Int.to_string;

    eval_test (fun () ->
        size (T (B, T (B, E, 1, E), 1, T (B, E, 1, E))), 3)
       "size (T (B, T (B, E, 1, E), 1, T (B, E, 1, E)))"
        Int.to_string;

    (* some is_bst tests *)
    eval_test (fun () ->
        is_bst E, true)
       "is_bst E"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (T (B, E, 1, E)), true)
       "is_bst (T (B, E, 1, E))"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (T (B, T (R, E, 1, E), 2, T (R, E, 3, E))), true)
       "is_bst (T (B, T (R, E, 1, E), 2, T (R, E, 3, E)))"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (T (B, T (R, T (B, E, 1, E), 2, T (B, E, 3, E)), 4, T (B, E, 5, E))), true)
       "is_bst (T (B, T (R, T (B, E, 1, E), 2, T (B, E, 3, E)), 4, T (B, E, 5, E)))"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (T (B, T (R, T (B, E, 2, E), 1, E), 3, E)), false)
       "is_bst (T (B, T (R, T (B, E, 2, E), 1, E), 3, E))"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (T (B, E, 2, T (R, T (B, E, 1, E), 3, E))), false)
       "is_bst (T (B, E, 2, T (R, T (B, E, 1, E), 3, E)))"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (T (B, T (R, T (B, T (B, E, 1, E), 2, E), 3, E), 1, E)), false)
       "is_bst (T (B, T (R, T (B, T (B, E, 1, E), 2, E), 3, E), 1, E))"
        Bool.to_string;

    (* some is_red_black_tree tests *)
    eval_test (fun () ->
        is_red_black_tree E, true)
       "is_red_black_tree E"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (T (B, E, 1, E)), true)
       "is_red_black_tree (T (B, E, 1, E))"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (T (B, T (R, E, 1, E), 2, T (R, E, 3, E))), true)
       "is_red_black_tree (T (B, T (R, E, 1, E), 2, T (R, E, 3, E)))"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (T (B, T (R, T (B, E, 1, E), 2, T (B, E, 3, E)), 4, T (B, E, 5, E))), true)
       "is_red_black_tree (T (B, T (R, T (B, E, 1, E), 2, T (B, E, 3, E)), 4, T (B, E, 5, E)))"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (T (R, T (R, E, 1, E), 2, T (B, E, 3, E))), false)
       "is_red_black_tree (T (R, T (R, E, 1, E), 2, T (B, E, 3, E)))"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (T (R, T (B, E, 1, E), 2, T (R, E, 3, E))), false)
       "is_red_black_tree (T (R, T (B, E, 1, E), 2, T (R, E, 3, E)))"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (T (B, T (B, E, 1, E), 2, T (R, E, 3, E))), false)
       "is_red_black_tree (T (B, T (B, E, 1, E), 2, T (R, E, 3, E)))"
        Bool.to_string;

    eval_test (fun () ->
        is_red_black_tree (T (B, T (R, T (B, E, 1, E), 2, T (R, E, 3, E)), 4, T (B, E, 5, E))), false)
       "is_red_black_tree (T (B, T (R, T (B, E, 1, E), 2, T (R, E, 3, E)), 4, T (B, E, 5, E)))"
        Bool.to_string;

    ]

  let run () = run_tests some_tests

end
