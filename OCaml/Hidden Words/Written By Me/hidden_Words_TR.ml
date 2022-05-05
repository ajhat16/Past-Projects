open SetSig
open Hidden_Words_Sig
open Util

(* This module is meant to include only tail recursive functions.
 *)
module HiddenImpl_TR_F (S: SetS)  = struct

  (* There may be other helper functions defined here. *)

  let try_2_words (words8: string S.t) (w3: string) (w5: string) : 
        (string * string * string) list =
    match (UtilM.explode w3, UtilM.explode w5) with
    | ([], _) | ([_],_) | ([_;_],_) | (_, []) | (_, [_])
    | (_, [_;_]) | (_, [_;_;_]) | (_, [_;_;_;_]) -> []
    | ([a;b;c], [d;e;f;g;h]) ->
       let s1 = UtilM.implode [d;a;b;c;e;f;g;h] in
       let s2 = UtilM.implode [d;e;a;b;c;f;g;h] in
       let s3 = UtilM.implode [d;e;f;a;b;c;g;h] in
       let s4 = UtilM.implode [d;e;f;g;a;b;c;h] in
       if S.elem s1 words8 then [(w3,w5,s1)]
       else if S.elem s2 words8 then [(w3,w5,s2)]
       else if S.elem s3 words8 then [(w3,w5,s3)]
       else if S.elem s4 words8 then [(w3,w5,s4)]
       else []
    | _ -> []

  let hidden_words (word_list: string list) : (string * string * string) list =
    let w3s = List.filter (fun x -> String.length x = 3) word_list in
    let w5s = List.filter (fun x -> String.length x = 5) word_list in
    let rec make_eights (lst: string list) (set: string S.t) : string S.t =
      match lst with
      | [] -> set
      | s::ss when String.length s = 8 -> make_eights ss (S.insert s set)
      | s::ss -> make_eights ss set
    in
    let w8s = make_eights word_list S.empty in 
    let rec combo (w3: string list) (w5: string list) (orig: string list)
      (acc: (string * string * string) list): (string * string * string) list =
      match w3 with
      | [] -> acc
      | t::ts -> (match w5 with
                  | [] -> combo ts orig orig acc
                  | f::fs ->
                     let t2w = try_2_words w8s t f in
                     match t2w with
                     | [] -> combo w3 fs orig acc
                     | [x] -> combo w3 fs orig (x::acc)
                     | _ -> combo w3 fs orig acc
                  )
    in
    combo w3s w5s w5s []


end


(* Here we dfined the functor `HiddenF`. It uses the `HiddenImplF`
   functor but only exposes the `hidden_words` function that is
   defined in `HiddenS`.

   We will use `HiddenF` in `solution.ml` to create the list-based
   and the tree-based solutions to the problem.
 *)

module HiddenWords_TR_F (S: SetS) : HiddenS = HiddenImpl_TR_F(S)
