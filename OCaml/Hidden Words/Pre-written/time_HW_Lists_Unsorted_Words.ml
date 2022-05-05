open Hidden_Words
open Util

module HW = HiddenWordsF ( ListSet.ListSetM )

let word_file = "words-google-10000.txt"

let () = 
  print_endline "Original hidden-words with list based sets " ;
  print_endline (" on \"" ^ word_file ^ "\"...");
  let words = (UtilM.read_words word_file)
  in
  let answers = HW.hidden_words words
  in
  UtilM.print_answers answers
