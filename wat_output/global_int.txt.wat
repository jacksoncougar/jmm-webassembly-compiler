;;begins auto generated .wasm code
(module
  ;;externs/imports
  (import "host" "exit" (func $halt))
  (import "host" "getchar" (func $getchar (result i32)))
  (import "host" "putchar" (func $putchar (param i32)))
  ;;data
  (data 0 (i32.const 0) "true")
  (data 0 (i32.const 4) "false")
  (global $0 (mut i32) (i32.const 0))
  ;;program
  ;;begins auto generated .wasm code
  (start $main)
  (func $main
    (block $L0
      ;;unaryexpression negation
      i32.const  103
      i32.const -1
      i32.xor
      i32.const 1
      i32.add
      ;;end negation
      global.set $0
      global.get $0
      call $printi
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
    (param $1 i32);;i
    (local $2 i32);;digit
    (local $3 i32);;divisor
    (local $4 i32);;remainder
    (local $5 i32);;lz
    (local $6 i32);;negative
    (block $L1
      i32.const 0;;boolean false
      local.set $6
      i32.const  0
      local.set $5
      i32.const  1000000000
      local.set $3
      local.get $1
      local.set $4
      i32.const  0
      local.set $2
      ;;if condition
      local.get $4
      i32.const  0
      i32.lt_s
      (if
        (then
          (block $L2
            i32.const  45
            call $putchar
            i32.const 1;;boolean true
            local.set $6
          )
        )
      )
      (block $L3
        (loop $L4
          ;;loop condition
          local.get $5
          i32.const  0
          i32.eq
          local.get $3
          i32.const  0
          i32.gt_s
          i32.and
          ;;loop test
          i32.eqz
          br_if $L3
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L5
            local.get $4
            local.get $3
            i32.div_s
            local.set $5
            local.get $4
            local.get $3
            i32.rem_s
            local.set $4
            local.get $3
            i32.const  10
            i32.div_s
            local.set $3
          )
          ;;finished auto generated .wasm code
          br $L4
        )
      )
      local.get $5
      local.set $2
      (block $L6
        (loop $L7
          ;;loop condition
          local.get $3
          i32.const  0
          i32.gt_s
          ;;loop test
          i32.eqz
          br_if $L6
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L8
            ;;if condition
            local.get $6
            (if
              (then
                (block $L9
                  i32.const  48
                  i32.const  0
                  local.get $2
                  i32.sub
                  i32.add
                  call $putchar
                )
              )
              (else
                (block $L10
                  i32.const  48
                  local.get $2
                  i32.add
                  call $putchar
                )
              )
            )
            local.get $4
            local.get $3
            i32.div_s
            local.set $2
            local.get $4
            local.get $3
            i32.rem_s
            local.set $4
            local.get $3
            i32.const  10
            i32.div_s
            local.set $3
          )
          ;;finished auto generated .wasm code
          br $L7
        )
      )
      ;;if condition
      local.get $6
      (if
        (then
          (block $L11
            i32.const  48
            i32.const  0
            local.get $2
            i32.sub
            i32.add
            call $putchar
          )
        )
        (else
          (block $L12
            i32.const  48
            local.get $2
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
    (param $7 i32);;b
    (block $L13
      ;;if condition
      local.get $7
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
    (param $8 i32);;c
    (block $L14
      local.get $8
      call $putchar
    )
  )
  ;;finished auto generated .wasm code
  
  (memory 1)
);;finished auto generated .wasm code
