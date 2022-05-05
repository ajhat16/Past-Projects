(* Types for values, expressions, and types in a small expression 
   language.
 *)

type value 
  = IntV of int
  | BoolV of bool

and  expr 
  = Val of value

  | Add of expr * expr
  | Sub of expr * expr
  | Mul of expr * expr
  | Div of expr * expr

  | Lt  of expr * expr
  | Lte  of expr * expr
  | Eq  of expr * expr
  | And of expr * expr
  | Or  of expr * expr
  | Not of expr

  | Id of string
  | Let of string * typ * expr * expr

and  typ
  = IntT
  | BoolT

(* Evaluation *)

type environment = (string * value) list

exception DivisionByZero of value

let rec eval (e: expr) (env: environment) : value =
  match e with
  | Val v -> v 
  | Add (e1, e2) -> 
     (match eval e1 env, eval e2 env with
      | IntV i1, IntV i2 -> IntV (i1 + i2)
      | _ -> raise (Failure "Internal Error on Add")
     )
  | Sub (e1, e2) -> 
     (match eval e1 env, eval e2 env with
      | IntV i1, IntV i2 -> IntV (i1 - i2)
      | _ -> raise (Failure "Internal Error on Sub")
     )
  | Mul (e1, e2) ->
     (match eval e1 env, eval e2 env with
      | IntV i1, IntV i2 -> IntV (i1 * i2)
      | _ -> raise (Failure "Internal Error on Mul")
     )
  | Div (e1, e2) ->
     (match eval e1 env, eval e2 env with
      | IntV i1, IntV i2 -> if i2 = 0 then raise (DivisionByZero (IntV i1))
                            else IntV (i1 / i2)
      | _ -> raise (Failure "Internal Error on Div")
     )
  | Lt (e1, e2) -> 
     (match eval e1 env, eval e2 env with
      | IntV i1, IntV i2 -> BoolV (i1 < i2)
      | _ -> raise (Failure "Internal Error on Lt")
     )
  | Lte (e1, e2) ->
     (match eval e1 env, eval e2 env with
      | IntV i1, IntV i2 -> BoolV (i1 <= i2)
      | _ -> raise (Failure "Internal Error on Lte")
     )
  | Eq (e1, e2) ->
     (match eval e1 env, eval e2 env with
      | IntV i1, IntV i2 -> BoolV (i1 = i2)
      | _ -> raise (Failure "Internal Error on Eq")
     )
  | And (e1, e2) ->
     (match eval e1 env, eval e2 env with
      | BoolV b1, BoolV b2 -> BoolV (b1 && b2)
      | _ -> raise (Failure "Internal Error on And")
     )
  | Or (e1, e2) ->
     (match eval e1 env, eval e2 env with
      | BoolV b1, BoolV b2 -> BoolV (b1 || b2)
      | _ -> raise (Failure "Internal Error on Or")
     )
  | Not e1 ->
     (match eval e1 env with
      | BoolV b1 -> BoolV (not b1)
      | _ -> raise (Failure "Internal Error on Not")
     )
  | Id s ->
     (* Inspired by a function written by Erik Van Wyk *)
     let rec search (str: string) (e: environment) : value =
       match e with
       | [] -> raise (Failure "Internal Error on Id")
       | (n, v)::es -> if str = n then v else search str es
     in
     search s env
  | Let (s, t, e1, e2) ->
     (* Inspired by a function written by Erik Van Wyk *)
     let binding : string * value = (s, eval e1 env) in
     eval e2 (binding::env)



type context = (string * typ) list

type typ_error = ExpectedInt | ExpectedBool | UndeclaredName

type 'a result = Result of 'a
               | Error of typ_error

let rec type_check (e: expr) (ctx: context) : typ result =
  match e with
  | Val (IntV _) -> Result IntT
  | Val (BoolV _) -> Result BoolT
  | Add (e1, e2) | Sub (e1, e2) | Mul (e1, e2) | Div (e1, e2)
  | Lte (e1,e2) | Lt (e1, e2) | Eq (e1, e2) -> 
     (match type_check e1 ctx, type_check e2 ctx with
      | Result IntT, Result IntT -> Result IntT
      | Result BoolT, _ -> Error ExpectedInt
      | Result IntT, Result BoolT -> Error ExpectedInt
      | Error err, _ -> Error err
      | _, Error err -> Error err
     )
  | And (e1, e2) | Or (e1, e2) ->
     (match type_check e1 ctx, type_check e2 ctx with
      | Result BoolT, Result BoolT -> Result BoolT
      | Result IntT, _ -> Error ExpectedBool
      | Result BoolT, Result IntT -> Error ExpectedBool
      | Error err, _ -> Error err
      | _, Error err -> Error err
     )
  | Not e1 ->
     (match type_check e1 ctx with
      | Result BoolT -> Result BoolT
      | Result IntT -> Error ExpectedBool
      | Error err -> Error err
     )
  | Id x ->
     (* Inspired by a function written by Erik Van Wyk *)
     let rec search (str: string) (c: context) : typ result =
       match c with
       | [] -> Error UndeclaredName
       | (n, t)::cs -> if n = str then Result t else search str cs                 
     in
     search x ctx
  | Let (name, t, e1, e2) ->
     (* Inspired by a function written by Erik Van Wyk *)
     let e1t : typ result = type_check e1 ctx
     in
     (match e1t with
      | Error err -> Error err
      | Result IntT when t <> IntT -> Error ExpectedBool
      | Result BoolT when t <> BoolT -> Error ExpectedInt
      | _ -> type_check e2 ( (name,t) :: ctx)
     )

(* This function should never raise an exception, even though a function
   that it calls will raise exceptions on some of its inputs.
   Why is that?
 *)
let evaluate (e: expr) : value result =
  match type_check e [] with
  | Result ty -> Result (eval e [])
  | Error err -> Error err
