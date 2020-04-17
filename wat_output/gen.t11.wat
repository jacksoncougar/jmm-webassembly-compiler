;;begins auto generated .wasm code
(module
  ;;externs/imports
  (import "host" "exit" (func $halt))
  (import "host" "getchar" (func $getchar (result i32)))
  (import "host" "putchar" (func $putchar (param i32)))
  ;;data
  (data 0 (i32.const 0) "true")
  (data 0 (i32.const 4) "false")
  (data 0 (i32.const 9) "\n(it's ok if the following aren't 0/false)\n")
  (data 0 (i32.const 54) "\tlocal int default value: ")
  (data 0 (i32.const 81) "\n")
  (data 0 (i32.const 83) "\tlocal boolean default value: ")
  (data 0 (i32.const 114) "global int default value: ")
  (data 0 (i32.const 140) "global boolean default value: ")
  (global $0 (mut i32) (i32.const 0))
  (global $1 (mut i32) (i32.const 0))
  ;;program
  ;;begins auto generated .wasm code
  (func $foo
    (local $2 i32);;i2
    (local $3 i32);;b2
    (block $L0
      i32.const 9
      i32.const 45
      call $prints
      i32.const 54
      i32.const 27
      call $prints
      local.get $2
      call $printi
      i32.const 81
      i32.const 2
      call $prints
      i32.const 83
      i32.const 31
      call $prints
      local.get $3
      call $printb
      i32.const 81
      i32.const 2
      call $prints
      i32.const  123
      local.set $2
      i32.const 1;;boolean true
      local.set $3
    )
  )
  (start $main)
  (func $main
    (block $L1
      i32.const 114
      i32.const 26
      call $prints
      global.get $0
      call $printi
      i32.const 81
      i32.const 2
      call $prints
      i32.const 140
      i32.const 30
      call $prints
      global.get $1
      call $printb
      i32.const 81
      i32.const 2
      call $prints
      call $foo
      call $foo
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
    (param $4 i32);;i
    (local $5 i32);;digit
    (local $6 i32);;divisor
    (local $7 i32);;remainder
    (local $8 i32);;lz
    (local $9 i32);;negative
    (block $L2
      i32.const 0;;boolean false
      local.set $9
      i32.const  0
      local.set $8
      i32.const  1000000000
      local.set $6
      local.get $4
      local.set $7
      i32.const  0
      local.set $5
      ;;if condition
      local.get $7
      i32.const  0
      i32.lt_s
      (if
        (then
          (block $L3
            i32.const  45
            call $putchar
            i32.const 1;;boolean true
            local.set $9
          )
        )
      )
      (block $L4
        (loop $L5
          ;;loop condition
          local.get $8
          i32.const  0
          i32.eq
          local.get $6
          i32.const  0
          i32.gt_s
          i32.and
          ;;loop test
          i32.eqz
          br_if $L4
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L6
            local.get $7
            local.get $6
            i32.div_s
            local.set $8
            local.get $7
            local.get $6
            i32.rem_s
            local.set $7
            local.get $6
            i32.const  10
            i32.div_s
            local.set $6
          )
          ;;finished auto generated .wasm code
          br $L5
        )
      )
      local.get $8
      local.set $5
      (block $L7
        (loop $L8
          ;;loop condition
          local.get $6
          i32.const  0
          i32.gt_s
          ;;loop test
          i32.eqz
          br_if $L7
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L9
            ;;if condition
            local.get $9
            (if
              (then
                (block $L10
                  i32.const  48
                  i32.const  0
                  local.get $5
                  i32.sub
                  i32.add
                  call $putchar
                )
              )
              (else
                (block $L11
                  i32.const  48
                  local.get $5
                  i32.add
                  call $putchar
                )
              )
            )
            local.get $7
            local.get $6
            i32.div_s
            local.set $5
            local.get $7
            local.get $6
            i32.rem_s
            local.set $7
            local.get $6
            i32.const  10
            i32.div_s
            local.set $6
          )
          ;;finished auto generated .wasm code
          br $L8
        )
      )
      ;;if condition
      local.get $9
      (if
        (then
          (block $L12
            i32.const  48
            i32.const  0
            local.get $5
            i32.sub
            i32.add
            call $putchar
          )
        )
        (else
          (block $L13
            i32.const  48
            local.get $5
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
    (param $10 i32);;b
    (block $L14
      ;;if condition
      local.get $10
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
    (param $11 i32);;c
    (block $L15
      local.get $11
      call $putchar
    )
  )
  ;;finished auto generated .wasm code
  
  (memory 1)
);;finished auto generated .wasm code
