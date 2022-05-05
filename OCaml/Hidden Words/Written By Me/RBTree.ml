
(* Below is a signature for red-black trees that exposes some
   implementation details to facilitate testing.
 *)

module type  RBTreeImplS = sig

  type color = R | B

  type 'a tree = E
               | T of color * 'a tree * 'a * 'a tree

  include RBTreeSig.RBTreeS with type 'a t = 'a tree

  (* You may add additiona functions below that you wish to
     expose so that they can be more easily tested.

     Some implementations of `is_red_black_tree` may use helper
     function and you may add them here to facilitate testing.
   *)

end

module RBTreeImplM : RBTreeImplS = struct

  type color = R | B

  type 'a tree = E
               | T of color * 'a tree * 'a * 'a tree

  type 'a t = 'a tree

  let empty = E
  (* Mostly written by Erik Van Wyk *)
  let balance c t1 v t2 = match c, t1, v, t2 with
      | B, T(R, T(R,a,x,b), y,c), z, d
      | B, T(R, a, x, T(R,b,y,c)), z, d
      | B, a, x, T(R, b, y, T(R,c,z,d))
      | B, a, x, T(R, T(R,b,y,c), z, d)
         -> T(R, T(B,a,x,b), y, T(B,c,z,d))
      | color, t1, v, t2 -> T (color, t1, v, t2)

  (* Written by Erik Van Wyk *)
  let rec insert (x: 'a) (tr: 'a tree) : 'a tree =
    let rec ins (t': 'a tree) : 'a tree =
      match t' with
      | E -> T (R, E, x, E)
      | T (c, t1, y, t2) ->
         if x < y
         then balance c (ins t1) y t2
         else if x > y
         then balance c t1 y (ins t2)
         else t'
    in
    match ins tr with
    | E -> failwith "Cannot happen, ins always returns a T tree"
    | T (_, t1, y, t2) -> T (B, t1, y, t2)

  (* Written by Erik Van Wyk *)
  let rec elem (x: 'a) (tr: 'a tree) : bool =
    match tr with
    | E -> false
    | T (_, t1, y, t2) ->
       if x < y
       then elem x t1
       else if x > y
       then elem x t2
       else true

  let rec height (tr: 'a tree) : int =
    match tr with
    | E -> 0
    | T (_,l,v,r) -> 1 + max (height l) (height r)

  let rec size (tr: 'a tree) : int = 
    match tr with
    | E -> 0
    | T (_,l,v,r) -> 1 + (size l) + (size r)

  let rec is_bst (t': 'a tree) : bool =
    let rec smaller (v: 'a) (tr: 'a tree) : bool =
      match tr with
      | E -> true
      | T (_,l,x,r) -> x < v && smaller v l && smaller v r
    in
    let rec bigger (v: 'a) (tr: 'a tree) : bool =
      match tr with
      | E -> true
      | T (_,l,x,r) -> x > v && bigger v l && bigger v r
    in
    match t' with
    | E -> true
    | T (_,E, v, E) -> true
    | T (_,T (c,l1,x,r1), v, E) ->
       x < v && smaller v (T (c,l1,x,r1))
       && is_bst (T (c,l1,x,r1))
    | T (_,E,v,T (c,l1,x,r1)) ->
       x > v && bigger v (T (c,l1,x,r1))
       && is_bst (T (c,l1,x,r1))
    | T (_,T (c1,l1,x,r1), v, T(c2,l2,y,r2)) ->
       x < v && y > v && smaller v (T (c1,l1,x,r1))
       && bigger v (T(c2,l2,y,r2)) && is_bst (T (c1,l1,x,r1))
       && is_bst (T(c2,l2,y,r2))

  let rec is_red_black_tree (tr: 'a t) : bool =
    if not (is_bst tr) then false
    else
      match tr with
      | E -> true
      | T (c, E, v, E) -> true
      | T (c, T (c1,l1,x,r1), v, E)
      | T (c, E, v, T (c1,l1,x,r1)) ->
         if c = R then c1 <> R &&
         is_red_black_tree (T (c1,l1,x,r1))
         else is_red_black_tree (T (c1,l1,x,r1))
      | T (c, T (c1,l1,x,r1), v, T (c2,l2,y,r2)) ->
         if c = R then c1 <> R && c2 <> R && 
         is_red_black_tree (T (c1,l1,x,r1)) &&
         is_red_black_tree (T (c2,l2,y,r2))
         else is_red_black_tree (T (c1,l1,x,r1)) &&
         is_red_black_tree (T (c2,l2,y,r2))

end



(* Below we create a new modules `RBTreeM` that only exposes the
   red-black tree functionality in the `RBTreeS` signature.
   Functions that may be useful for testing, such as `all_paths`
   are not accessible in `RBTreeM`.

   We "seal" `RBTreeM` with the signature `RBTreeS` so that it only
   exposes the elements of `RBTreeS`.   
*)
module RBTreeM : RBTreeSig.RBTreeS = RBTreeImplM



(* Below we create a new module `TreeSetM` that only exposes the
   set functionality in the `SetS` signature. Functions like
   `height` and `size` that are accessible in `RBTreeM` are not
   accessible in `RBTreeSetM`.

   We "seal" `RBTreeSetM` with the signature `SetS` so that is
   only exposes the elements of `SetS`.
 *)
module RBTreeBSTM : BSTreeSig.BSTreeS = RBTreeImplM



(* Below we create a new module `RBTreeSetM` that only exposes the
   set functionality in the `SetSig` signature. Functions like
   `height` and `size` that are accessible in `RBTreeM` are not
   accessible in `RBTreeSetM`.

   We "seal" `RBTreeSetM` with the signature `SetS` so that is
   only exposes the elements of `SetS`.
 *)
module RBTreeSetM : SetSig.SetS = RBTreeImplM
