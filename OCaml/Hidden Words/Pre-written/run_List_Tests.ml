
open ListSet

(* Set Tests *)
module ListTests = 
  Tests_for_Sets.Set_Tests (ListSetM)

let () = 
  print_endline 
    "\nRunning set signature tests for ListSet.\n";
  ListTests.run ()
