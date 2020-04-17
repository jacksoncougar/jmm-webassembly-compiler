;;begins auto generated .wasm code
(module
  ;;externs/imports
  (import "host" "exit" (func $halt))
  (import "host" "getchar" (func $getchar (result i32)))
  (import "host" "putchar" (func $putchar (param i32)))
  ;;data
  (data 0 (i32.const 0) "true")
  (data 0 (i32.const 4) "false")
  (data 0 (i32.const 9) "evaluated A\n")
  (data 0 (i32.const 22) "evaluated B\n")
  (data 0 (i32.const 35) "evaluated C\n")
  (data 0 (i32.const 48) "if ((A && B) || C) {...} else {...}, with A=")
  (data 0 (i32.const 92) " B=")
  (data 0 (i32.const 95) " C=")
  (data 0 (i32.const 98) "\n")
  (data 0 (i32.const 100) "if-part executed\n")
  (data 0 (i32.const 118) "else-part executed\n")
  (data 0 (i32.const 138) "x = (A && !B) || C, with A=")
  (data 0 (i32.const 165) "x=")
  (global $0 (mut i32) (i32.const 0))
  (global $1 (mut i32) (i32.const 0))
  (global $2 (mut i32) (i32.const 0))
  ;;program
  ;;begins auto generated .wasm code
  (func $A
    (result i32)
    (block $L0
      i32.const 9
      i32.const 13
      call $prints
      global.get $0
      return
    )
    i32.const 0
    return
  )
  (func $B
    (result i32)
    (block $L1
      i32.const 22
      i32.const 13
      call $prints
      global.get $1
      return
    )
    i32.const 0
    return
  )
  (func $C
    (result i32)
    (block $L2
      i32.const 35
      i32.const 13
      call $prints
      global.get $2
      return
    )
    i32.const 0
    return
  )
  (func $eval
    (param $3 i32);;newa
    (param $4 i32);;n00b
    (param $5 i32);;newc
    (block $L3
      local.get $3
      global.set $0
      local.get $4
      global.set $1
      local.get $5
      global.set $2
      i32.const 48
      i32.const 44
      call $prints
      global.get $0
      call $printb
      i32.const 92
      i32.const 3
      call $prints
      global.get $1
      call $printb
      i32.const 95
      i32.const 3
      call $prints
      global.get $2
      call $printb
      i32.const 98
      i32.const 2
      call $prints
      ;;if condition
      call $A
      call $B
      i32.and
      call $C
      i32.or
      (if
        (then
          (block $L4
            i32.const 100
            i32.const 18
            call $prints
          )
        )
        (else
          (block $L5
            i32.const 118
            i32.const 20
            call $prints
          )
        )
      )
    )
  )
  (func $assign
    (param $6 i32);;newa
    (param $7 i32);;newb
    (param $8 i32);;newc
    (local $9 i32);;x
    (block $L6
      local.get $6
      global.set $0
      local.get $7
      global.set $1
      local.get $8
      global.set $2
      i32.const 138
      i32.const 27
      call $prints
      global.get $0
      call $printb
      i32.const 92
      i32.const 3
      call $prints
      global.get $1
      call $printb
      i32.const 95
      i32.const 3
      call $prints
      global.get $2
      call $printb
      i32.const 98
      i32.const 2
      call $prints
      call $A
      ;;boolean negation
      call $B
      i32.const 1
      i32.add
      i32.const 2
      i32.rem_u
      ;;end negation
      i32.and
      call $C
      i32.or
      local.set $9
      i32.const 165
      i32.const 2
      call $prints
      local.get $9
      call $printb
      i32.const 98
      i32.const 2
      call $prints
    )
  )
  (start $main)
  (func $main
    (block $L7
      i32.const 0;;boolean false
      i32.const 0;;boolean false
      i32.const 0;;boolean false
      call $eval
      i32.const 98
      i32.const 2
      call $prints
      i32.const 0;;boolean false
      i32.const 0;;boolean false
      i32.const 1;;boolean true
      call $eval
      i32.const 98
      i32.const 2
      call $prints
      i32.const 0;;boolean false
      i32.const 1;;boolean true
      i32.const 0;;boolean false
      call $eval
      i32.const 98
      i32.const 2
      call $prints
      i32.const 0;;boolean false
      i32.const 1;;boolean true
      i32.const 1;;boolean true
      call $eval
      i32.const 98
      i32.const 2
      call $prints
      i32.const 1;;boolean true
      i32.const 0;;boolean false
      i32.const 0;;boolean false
      call $eval
      i32.const 98
      i32.const 2
      call $prints
      i32.const 1;;boolean true
      i32.const 0;;boolean false
      i32.const 1;;boolean true
      call $eval
      i32.const 98
      i32.const 2
      call $prints
      i32.const 1;;boolean true
      i32.const 1;;boolean true
      i32.const 0;;boolean false
      call $eval
      i32.const 98
      i32.const 2
      call $prints
      i32.const 1;;boolean true
      i32.const 1;;boolean true
      i32.const 1;;boolean true
      call $eval
      i32.const 98
      i32.const 2
      call $prints
      i32.const 0;;boolean false
      i32.const 0;;boolean false
      i32.const 0;;boolean false
      call $assign
      i32.const 98
      i32.const 2
      call $prints
      i32.const 0;;boolean false
      i32.const 0;;boolean false
      i32.const 1;;boolean true
      call $assign
      i32.const 98
      i32.const 2
      call $prints
      i32.const 0;;boolean false
      i32.const 1;;boolean true
      i32.const 0;;boolean false
      call $assign
      i32.const 98
      i32.const 2
      call $prints
      i32.const 0;;boolean false
      i32.const 1;;boolean true
      i32.const 1;;boolean true
      call $assign
      i32.const 98
      i32.const 2
      call $prints
      i32.const 1;;boolean true
      i32.const 0;;boolean false
      i32.const 0;;boolean false
      call $assign
      i32.const 98
      i32.const 2
      call $prints
      i32.const 1;;boolean true
      i32.const 0;;boolean false
      i32.const 1;;boolean true
      call $assign
      i32.const 98
      i32.const 2
      call $prints
      i32.const 1;;boolean true
      i32.const 1;;boolean true
      i32.const 0;;boolean false
      call $assign
      i32.const 98
      i32.const 2
      call $prints
      i32.const 1;;boolean true
      i32.const 1;;boolean true
      i32.const 1;;boolean true
      call $assign
    )
  )
  ;;finished auto generated .wasm code
  ;;runtime system
  
  ;;
  (func $prints (; 1 ;) (param $0 i32) (param $1 i32)
    (block $label$0
     (br_if $label$0
      (i32.lt_s
       (get_local $1)
       (i32.const 1)
      )
     )
     (loop $label$1
       (call $putchar
        (i32.load8_s
         (get_local $0)
        )
      )
      (set_local $0
       (i32.add
        (get_local $0)
        (i32.const 1)
       )
      )
      (br_if $label$1
       (tee_local $1
        (i32.add
         (get_local $1)
         (i32.const -1)
        )
       )
      )
     )
    )
  )
  ;;begins auto generated .wasm code
  (func $printi
    (param $10 i32);;i
    (local $11 i32);;digit
    (local $12 i32);;divisor
    (local $13 i32);;remainder
    (local $14 i32);;lz
    (local $15 i32);;negative
    (block $L8
      i32.const 0;;boolean false
      local.set $15
      i32.const  0
      local.set $14
      i32.const  1000000000
      local.set $12
      local.get $10
      local.set $13
      i32.const  0
      local.set $11
      ;;if condition
      local.get $13
      i32.const  0
      i32.lt_s
      (if
        (then
          (block $L9
            i32.const  45
            call $putchar
            i32.const 1;;boolean true
            local.set $15
          )
        )
      )
      (block $L10
        (loop $L11
          ;;loop condition
          local.get $14
          i32.const  0
          i32.eq
          local.get $12
          i32.const  0
          i32.gt_s
          i32.and
          ;;loop test
          i32.eqz
          br_if $L10
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L12
            local.get $13
            local.get $12
            i32.div_s
            local.set $14
            local.get $13
            local.get $12
            i32.rem_s
            local.set $13
            local.get $12
            i32.const  10
            i32.div_s
            local.set $12
          )
          ;;finished auto generated .wasm code
          br $L11
        )
      )
      local.get $14
      local.set $11
      (block $L13
        (loop $L14
          ;;loop condition
          local.get $12
          i32.const  0
          i32.gt_s
          ;;loop test
          i32.eqz
          br_if $L13
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L15
            ;;if condition
            local.get $15
            (if
              (then
                (block $L16
                  i32.const  48
                  i32.const  0
                  local.get $11
                  i32.sub
                  i32.add
                  call $putchar
                )
              )
              (else
                (block $L17
                  i32.const  48
                  local.get $11
                  i32.add
                  call $putchar
                )
              )
            )
            local.get $13
            local.get $12
            i32.div_s
            local.set $11
            local.get $13
            local.get $12
            i32.rem_s
            local.set $13
            local.get $12
            i32.const  10
            i32.div_s
            local.set $12
          )
          ;;finished auto generated .wasm code
          br $L14
        )
      )
      ;;if condition
      local.get $15
      (if
        (then
          (block $L18
            i32.const  48
            i32.const  0
            local.get $11
            i32.sub
            i32.add
            call $putchar
          )
        )
        (else
          (block $L19
            i32.const  48
            local.get $11
            i32.add
            call $putchar
          )
        )
      )
    )
  )
  ;;finished auto generated .wasm code
  
  ;;begins auto generated .wasm code
  (func $printb
    (param $16 i32);;b
    (block $L20
      ;;if condition
      local.get $16
      (if
        (then
          i32.const 0
          i32.const 4
          call $prints
        )
        (else
          i32.const 4
          i32.const 5
          call $prints
        )
      )
    )
  )
  ;;finished auto generated .wasm code
  
  ;;begins auto generated .wasm code
  (func $printc
    (param $17 i32);;c
    (block $L21
      local.get $17
      call $putchar
    )
  )
  ;;finished auto generated .wasm code
  
  (memory 1)
);;finished auto generated .wasm code
