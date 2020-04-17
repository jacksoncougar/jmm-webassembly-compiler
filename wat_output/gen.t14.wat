;;begins auto generated .wasm code
(module
  ;;externs/imports
  (import "host" "exit" (func $halt))
  (import "host" "getchar" (func $getchar (result i32)))
  (import "host" "putchar" (func $putchar (param i32)))
  ;;data
  (data 0 (i32.const 0) "true")
  (data 0 (i32.const 4) "false")
  (data 0 (i32.const 9) "minint is ")
  (data 0 (i32.const 19) "\n")
  ;;program
  ;;begins auto generated .wasm code
  (start $main)
  (func $main
    (local $0 i32);;i
    (local $1 i32);;delta
    (block $L0
      i32.const  0
      local.set $0
      i32.const  1000000
      local.set $1
      (block $L1
        (loop $L2
          ;;loop condition
          local.get $0
          local.get $0
          local.get $1
          i32.sub
          i32.gt_s
          ;;loop test
          i32.eqz
          br_if $L1
          ;;loop body
          ;;begins auto generated .wasm code
          local.get $0
          local.get $1
          i32.add
          local.set $0
          ;;finished auto generated .wasm code
          br $L2
        )
      )
      local.get $0
      local.get $1
      i32.sub
      local.set $0
      (block $L3
        (loop $L4
          ;;loop condition
          local.get $0
          local.get $0
          i32.const  1
          i32.sub
          i32.gt_s
          ;;loop test
          i32.eqz
          br_if $L3
          ;;loop body
          ;;begins auto generated .wasm code
          local.get $0
          i32.const  1
          i32.add
          local.set $0
          ;;finished auto generated .wasm code
          br $L4
        )
      )
      i32.const 9
      i32.const 10
      call $prints
      local.get $0
      call $printi
      i32.const 19
      i32.const 2
      call $prints
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
    (param $2 i32);;i
    (local $3 i32);;digit
    (local $4 i32);;divisor
    (local $5 i32);;remainder
    (local $6 i32);;lz
    (local $7 i32);;negative
    (block $L5
      i32.const 0;;boolean false
      local.set $7
      i32.const  0
      local.set $6
      i32.const  1000000000
      local.set $4
      local.get $2
      local.set $5
      i32.const  0
      local.set $3
      ;;if condition
      local.get $5
      i32.const  0
      i32.lt_s
      (if
        (then
          (block $L6
            i32.const  45
            call $putchar
            i32.const 1;;boolean true
            local.set $7
          )
        )
      )
      (block $L7
        (loop $L8
          ;;loop condition
          local.get $6
          i32.const  0
          i32.eq
          local.get $4
          i32.const  0
          i32.gt_s
          i32.and
          ;;loop test
          i32.eqz
          br_if $L7
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L9
            local.get $5
            local.get $4
            i32.div_s
            local.set $6
            local.get $5
            local.get $4
            i32.rem_s
            local.set $5
            local.get $4
            i32.const  10
            i32.div_s
            local.set $4
          )
          ;;finished auto generated .wasm code
          br $L8
        )
      )
      local.get $6
      local.set $3
      (block $L10
        (loop $L11
          ;;loop condition
          local.get $4
          i32.const  0
          i32.gt_s
          ;;loop test
          i32.eqz
          br_if $L10
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L12
            ;;if condition
            local.get $7
            (if
              (then
                (block $L13
                  i32.const  48
                  i32.const  0
                  local.get $3
                  i32.sub
                  i32.add
                  call $putchar
                )
              )
              (else
                (block $L14
                  i32.const  48
                  local.get $3
                  i32.add
                  call $putchar
                )
              )
            )
            local.get $5
            local.get $4
            i32.div_s
            local.set $3
            local.get $5
            local.get $4
            i32.rem_s
            local.set $5
            local.get $4
            i32.const  10
            i32.div_s
            local.set $4
          )
          ;;finished auto generated .wasm code
          br $L11
        )
      )
      ;;if condition
      local.get $7
      (if
        (then
          (block $L15
            i32.const  48
            i32.const  0
            local.get $3
            i32.sub
            i32.add
            call $putchar
          )
        )
        (else
          (block $L16
            i32.const  48
            local.get $3
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
    (param $8 i32);;b
    (block $L17
      ;;if condition
      local.get $8
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
    (param $9 i32);;c
    (block $L18
      local.get $9
      call $putchar
    )
  )
  ;;finished auto generated .wasm code
  
  (memory 1)
);;finished auto generated .wasm code
