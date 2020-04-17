;;begins auto generated .wasm code
(module
  ;;externs/imports
  (import "host" "exit" (func $halt))
  (import "host" "getchar" (func $getchar (result i32)))
  (import "host" "putchar" (func $putchar (param i32)))
  ;;data
  (data 0 (i32.const 0) "true")
  (data 0 (i32.const 4) "false")
  (data 0 (i32.const 9) " = \n")
  (data 0 (i32.const 14) "\t")
  (data 0 (i32.const 16) " (base 2)\n")
  (data 0 (i32.const 27) " (base 8)\n")
  (data 0 (i32.const 38) " (base 10)\n")
  ;;program
  ;;begins auto generated .wasm code
  (func $convert
    (param $0 i32);;n
    (param $1 i32);;base
    (block $L0
      ;;if condition
      local.get $0
      i32.const  0
      i32.eq
      (if
        (then
          (block $L1
            i32.const  0
            call $printi
            return
          )
        )
      )
      local.get $0
      local.get $1
      i32.div_s
      local.get $1
      call $convert
      local.get $0
      local.get $1
      i32.rem_s
      call $printi
    )
  )
  (func $do
    (param $2 i32);;i
    (block $L2
      local.get $2
      call $printi
      i32.const 9
      i32.const 5
      call $prints
      i32.const 14
      i32.const 2
      call $prints
      local.get $2
      i32.const  2
      call $convert
      i32.const 16
      i32.const 11
      call $prints
      i32.const 14
      i32.const 2
      call $prints
      local.get $2
      i32.const  8
      call $convert
      i32.const 27
      i32.const 11
      call $prints
      i32.const 14
      i32.const 2
      call $prints
      local.get $2
      i32.const  10
      call $convert
      i32.const 38
      i32.const 12
      call $prints
    )
  )
  (start $main)
  (func $main
    (block $L3
      i32.const  0
      call $do
      i32.const  17
      call $do
      i32.const  42
      call $do
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
    (param $3 i32);;i
    (local $4 i32);;digit
    (local $5 i32);;divisor
    (local $6 i32);;remainder
    (local $7 i32);;lz
    (local $8 i32);;negative
    (block $L4
      i32.const 0;;boolean false
      local.set $8
      i32.const  0
      local.set $7
      i32.const  1000000000
      local.set $5
      local.get $3
      local.set $6
      i32.const  0
      local.set $4
      ;;if condition
      local.get $6
      i32.const  0
      i32.lt_s
      (if
        (then
          (block $L5
            i32.const  45
            call $putchar
            i32.const 1;;boolean true
            local.set $8
          )
        )
      )
      (block $L6
        (loop $L7
          ;;loop condition
          local.get $7
          i32.const  0
          i32.eq
          local.get $5
          i32.const  0
          i32.gt_s
          i32.and
          ;;loop test
          i32.eqz
          br_if $L6
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L8
            local.get $6
            local.get $5
            i32.div_s
            local.set $7
            local.get $6
            local.get $5
            i32.rem_s
            local.set $6
            local.get $5
            i32.const  10
            i32.div_s
            local.set $5
          )
          ;;finished auto generated .wasm code
          br $L7
        )
      )
      local.get $7
      local.set $4
      (block $L9
        (loop $L10
          ;;loop condition
          local.get $5
          i32.const  0
          i32.gt_s
          ;;loop test
          i32.eqz
          br_if $L9
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L11
            ;;if condition
            local.get $8
            (if
              (then
                (block $L12
                  i32.const  48
                  i32.const  0
                  local.get $4
                  i32.sub
                  i32.add
                  call $putchar
                )
              )
              (else
                (block $L13
                  i32.const  48
                  local.get $4
                  i32.add
                  call $putchar
                )
              )
            )
            local.get $6
            local.get $5
            i32.div_s
            local.set $4
            local.get $6
            local.get $5
            i32.rem_s
            local.set $6
            local.get $5
            i32.const  10
            i32.div_s
            local.set $5
          )
          ;;finished auto generated .wasm code
          br $L10
        )
      )
      ;;if condition
      local.get $8
      (if
        (then
          (block $L14
            i32.const  48
            i32.const  0
            local.get $4
            i32.sub
            i32.add
            call $putchar
          )
        )
        (else
          (block $L15
            i32.const  48
            local.get $4
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
    (param $9 i32);;b
    (block $L16
      ;;if condition
      local.get $9
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
    (param $10 i32);;c
    (block $L17
      local.get $10
      call $putchar
    )
  )
  ;;finished auto generated .wasm code
  
  (memory 1)
);;finished auto generated .wasm code
