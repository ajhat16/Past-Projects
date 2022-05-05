
(* Below is a signature for binary search trees that exposes some
   implementation details to facilite testing.
 *)

module type  BSTreeImplS = sig
  type 'a tree = Leaf
               | Fork of 'a tree * 'a * 'a tree

  include BSTreeSig.BSTreeS with type 'a t = 'a tree

  (* You may add additiona functions below that you wish to
     expose so that they can be more easily tested.

     Some implementations of `is_bst` may use a function 
     `min_tree` and thus add the following to this signature:

     val min_tree : 'a tree -> 'a option

     You may add what ever functions you like here. Then add
     tests for them in `BSTreeSet_Tests_Impl.ml`
   *)

end


module BSTreeImplM : BSTreeImplS = struct

  type 'a tree = Leaf
               | Fork of 'a tree * 'a * 'a tree

  type 'a t = 'a tree


  let empty = Leaf

  let rec insert (e: 'a) (bst: 'a tree) : 'a tree =
    match bst with
	  | Leaf -> Fork (Leaf, e, Leaf)
	  | Fork (l, v, r) -> if e < v
	  			             then let nt = insert e l in
	  			     	       Fork (nt, v, r)
	  			             else if e > v
	  			             then let nt = insert e r in
	  			             	  Fork (l, v, nt)
	  			             else bst

  let rec elem (e: 'a) (bst: 'a tree) : bool =
    match bst with
    | Leaf -> false
    | Fork (l,v,r) -> if e < v then
                      elem e l
                      else if e > v then
                      elem e r
                      else true

  let rec height (bst: 'a tree) : int =
    match bst with
    | Leaf -> 0
    | Fork (l,v,r) -> 1 + max (height l) (height r)

  let rec size (bst: 'a tree) : int =
    match bst with
    | Leaf -> 0
    | Fork (l,v,r) -> 1 + (size l) + (size r)

  let rec is_bst (bst: 'a tree) : bool =
    let rec smaller (v: 'a) (tr: 'a tree) : bool =
      match tr with
      | Leaf -> true
      | Fork (l,x,r) -> x < v && smaller v l && smaller v r
    in
    let rec bigger (v: 'a) (tr: 'a tree) : bool =
      match tr with
      | Leaf -> true
      | Fork (l,x,r) -> x > v && bigger v l && bigger v r
    in
    match bst with
    | Leaf -> true
    | Fork (Leaf, v, Leaf) -> true
    | Fork (Fork (l1,x,r1), v, Leaf) ->
       x < v && smaller v (Fork (l1,x,r1))
       && is_bst (Fork (l1,x,r1))
    | Fork (Leaf,v,Fork (l1,x,r1)) ->
       x > v && bigger v (Fork (l1,x,r1))
       && is_bst (Fork (l1,x,r1))
    | Fork (Fork (l1,x,r1), v, Fork(l2,y,r2)) ->
       x < v && y > v && smaller v (Fork (l1,x,r1))
       && bigger v (Fork(l2,y,r2)) && is_bst (Fork (l1,x,r1))
       && is_bst (Fork(l2,y,r2))

end



(* Below we create a new moduled `BSTreeM` that only exposes the
   binary-search tree functionality in the BSTreeS` signature.
   Functions that may be useful for testing, such as `tree_min`
   are not accessible in `BSTreeM`.

   We "seal" `BSTreeM` with the signature `BSTreeS` so that it only
   exposes the elements of `BSTreeS`.
 *)
module BSTreeM : BSTreeSig.BSTreeS = BSTreeImplM



(* Below we create a new module `TreeSetM` that only exposes the
   set functionality in the `SetS` signature. Functions like
   `height` and `size` that are accessible in `TreeM` are not
   accessible in `TreeSetM`.

   We "seal" `TreeSetM` with the signature `SetS` so that is
   only exposes the elements of `SetS`.
 *)
module BSTreeSetM : SetSig.SetS = BSTreeM


