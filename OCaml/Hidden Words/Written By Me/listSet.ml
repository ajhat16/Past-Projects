open SetSig

(* Below add you implementation of sets as lists. Since these are
   pretty simple we do not build a separate version for testing 
   like we see in `BSTreeSet.ml` or `RBTreeSet.ml`.
 *)

module ListSetM : SetS = struct

  type 'a t = Nil
              | Cons of 'a * 'a t

  let empty = Nil

  let insert e lst = Cons (e, lst)

  let rec elem (e: 'a) (lst: 'a t) : bool = 
    match lst with
    | Nil -> false
    | Cons (x, xs) -> if e = x then true
                      else elem e xs
end

