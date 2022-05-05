open Hidden_Words_TR
open Util

module HW = HiddenWords_TR_F ( BSTree.BSTreeSetM )

let word_file = "words-google-10000.txt"

let () = 
  print_endline "Tail recursive hidden-words with binary search tree based sets " ;
  print_endline (" on \"" ^ word_file ^ "\"...");
  let words = (UtilM.read_words word_file)
  in
  let answers = HW.hidden_words words
  in
  UtilM.print_answers answers
