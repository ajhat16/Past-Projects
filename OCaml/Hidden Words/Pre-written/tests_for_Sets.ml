open Tests
open SetSig

(* The tests here are elements of the `SetS` signature.

   Thus they test `empty`, `insert`, and `elem` but only for
   values constructed by `empty` and `insert`. 
 *)

module Set_Tests (S: SetS) = struct

  open S

  let some_tests = [
    eval_test (fun () ->
        elem 2 (List.fold_right insert [3;1;2] empty), true)
       "elem 2 (List.fold_right insert [3;1;2] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 2 (List.fold_right insert [1;2;3] empty), true)
       "elem 2 (List.fold_right insert [1;2;3] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 2 (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty), true)
       "elem 2 (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 2 (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty), true)
       "elem 2 (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 4 (insert  4 (List.fold_right insert [3;1;2] empty)), true)
       "elem 4 (insert  4 (List.fold_right insert [3;1;2] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 4 (insert  4 (List.fold_right insert [1;2;3] empty)), true)
       "elem 4 (insert  4 (List.fold_right insert [1;2;3] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 4 (insert  4 (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty)), true)
       "elem 4 (insert  4 (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 4 (insert  4 (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty)), true)
       "elem 4 (insert  4 (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 15 (List.fold_right insert [3;1;2] empty), false)
       "elem 15 (List.fold_right insert [3;1;2] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 15 (List.fold_right insert [1;2;3] empty), false)
       "elem 15 (List.fold_right insert [1;2;3] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 15 (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty), false)
       "elem 15 (List.fold_right insert [10;9;8;7;6;5;4;3;2;1] empty))"
        Bool.to_string;

    eval_test (fun () ->
        elem 15 (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty), false)
       "elem 15 (List.fold_right insert [10;9;6;7;8;1;2;4;3;5] empty))"
        Bool.to_string;
    ]

  let run () = run_tests some_tests

end
