open Tests
open BSTree

(* The tests here are for the `BSTreeImplM` implementation. The tests
   thus have access to all elements of the `BSTreeImplS` signature.
 
   Importantly, this includes the tree constructors `Leaf` and `Fork` 
   that are not accessible to tests limited in their view by the
   `BSTreeS` signature.

   Having access to these constructors allows us to create trees directly
   instead of via `empty` and `insert` and then to test our `height`, 
   `size`, and `is_bst` functions.
 *)

module BSTree_Tests (T: BSTreeImplS) = struct

  open T

  let some_tests = [

    (* some height tests *)
    eval_test (fun () ->
        height Leaf, 0)
       "height Leaf"
        Int.to_string;

    eval_test (fun () ->
        height (Fork (Leaf, 1, Leaf)), 1)
       "height (Fork (Leaf, 1, Leaf))"
        Int.to_string;

    eval_test (fun () ->
        height (Fork (Fork (Leaf, 1, Leaf), 1, Leaf)), 2)
       "height (Fork (Fork (Leaf, 1, Leaf), 1, Leaf))"
        Int.to_string;

    eval_test (fun () ->
        height (Fork (Fork (Leaf, 1, Leaf), 1, Fork (Leaf, 1, Leaf))), 2)
       "height (Fork (Fork (Leaf, 1, Leaf), 1, Fork (Leaf, 1, Leaf)))"
        Int.to_string;

    eval_test (fun () ->
        height (List.fold_right insert [3;2;1] empty), 3)
       "height (List.fold_right insert [3;2;1] empty)"
        Int.to_string;

    eval_test (fun () ->
        height (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty) = 10, true)
       "height (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty) = 10"
        Bool.to_string;


    (* some size tests *)
    eval_test (fun () ->
        size Leaf, 0)
       "size Leaf"
        Int.to_string;

    eval_test (fun () ->
        size (Fork (Leaf, 1, Leaf)), 1)
       "size (Fork (Leaf, 1, Leaf))"
        Int.to_string;

    eval_test (fun () ->
        size (Fork (Fork (Leaf, 1, Leaf), 1, Leaf)), 2)
       "size (Fork (Fork (Leaf, 1, Leaf), 1, Leaf))"
        Int.to_string;

    eval_test (fun () ->
        size (Fork (Fork (Leaf, 1, Leaf), 1, Fork (Leaf, 1, Leaf))), 3)
       "size (Fork (Fork (Leaf, 1, Leaf), 1, Fork (Leaf, 1, Leaf)))"
        Int.to_string;

    (* some is_bst tests *)
    eval_test (fun () ->
        is_bst Leaf, true)
       "is_bst Leaf"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (Fork (Leaf, 1, Leaf)), true)
       "is_bst (Fork (Leaf, 1, Leaf))"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (Fork (Fork (Leaf, 1, Leaf), 2, Fork (Leaf, 3, Leaf))), true)
       "is_bst (Fork (Fork (Leaf, 1, Leaf), 2, Fork (Leaf, 3, Leaf)))"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (Fork (Fork (Fork (Leaf, 1, Leaf), 2, Fork (Leaf, 3, Leaf)), 4, Fork (Leaf, 5, Leaf))), true)
       "is_bst (Fork (Fork (Fork (Leaf, 1, Leaf), 2, Fork (Leaf, 3, Leaf)), 4, Fork (Leaf, 5, Leaf)))"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (Fork (Fork (Fork (Leaf, 2, Leaf), 1, Leaf), 3, Leaf)), false)
       "is_bst (Fork (Fork (Fork (Leaf, 2, Leaf), 1, Leaf), 3, Leaf))"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (Fork (Leaf, 2, Fork (Fork (Leaf, 1, Leaf), 3, Leaf))), false)
       "is_bst (Fork (Leaf, 2, Fork (Fork (Leaf, 1, Leaf), 3, Leaf)))"
        Bool.to_string;

    eval_test (fun () ->
        is_bst (Fork (Fork (Fork (Fork (Leaf, 1, Leaf), 2, Leaf), 3, Leaf), 1, Leaf)), false)
       "is_bst (Fork (Fork (Fork (Fork (Leaf, 1, Leaf), 2, Leaf), 3, Leaf), 1, Leaf))"
        Bool.to_string;
    ]

  let run () = run_tests some_tests

end
