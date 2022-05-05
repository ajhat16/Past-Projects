
open Tests
open Hidden_Words_Sig

module Hidden_Tests (S: HiddenS) = struct

  let sunday : string list = [ 
      "act"; "doldrums"; "drums"; "era"; "forth"; "fortieth"; "moribund"; 
      "mound"; "old"; "operatic"; "optic"; "practice"; "price"; "protrude"; 
      "prude"; "ran"; "relet"; "relevant"; "rib"; "rot"; "spa"; "tie"; 
      "trespass"; "tress"; "van"; "warranty"; "warty"
    ]

                           
  let some_tests = [

    eval_test (fun () ->
        List.mem ("act", "price", "practice") (S.hidden_words sunday), 
        true)
       "List.mem (\"act\", \"price\", \"practice\") (S.hidden_words sunday)"
        Bool.to_string;

    eval_test (fun () ->
        List.mem ("era", "optic", "operatic") (S.hidden_words sunday), 
        true)
       "List.mem (\"era\", \"optic\", \"operatic\") (S.hidden_words sunday)"
        Bool.to_string;

    eval_test (fun () ->
        List.length (S.hidden_words sunday), 9)
       "List.length (S.hidden_words sunday"
        Int.to_string

    ]

  let run () = run_tests some_tests

end


