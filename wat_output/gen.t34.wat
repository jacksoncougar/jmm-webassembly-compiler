;;begins auto generated .wasm code
(module
  ;;externs/imports
  (import "host" "exit" (func $halt))
  (import "host" "getchar" (func $getchar (result i32)))
  (import "host" "putchar" (func $putchar (param i32)))
  ;;data
  (data 0 (i32.const 0) "true")
  (data 0 (i32.const 4) "false")
  (data 0 (i32.const 9) "foo()\n")
  (data 0 (i32.const 16) "bar()\n")
  (data 0 (i32.const 23) "baz()\n")
  (data 0 (i32.const 30) "mane()\n")
  (data 0 (i32.const 38) "\n")
  (global $0 (mut i32) (i32.const 0))
  ;;program
  ;;begins auto generated .wasm code
  (func $foo
    (param $1 i32);;a
    (param $2 i32);;b
    (param $3 i32);;c
    (param $4 i32);;d
    (result i32)
    (block $L0
      i32.const 9
      i32.const 7
      call $prints
      local.get $1
      local.get $2
      i32.mul
      local.get $3
      i32.mul
      global.get $0
      i32.mul
      return
    )
    i32.const 0
    return
  )
  (func $bar
    (param $5 i32);;a
    (param $6 i32);;b
    (param $7 i32);;c
    (result i32)
    (block $L1
      i32.const 16
      i32.const 7
      call $prints
      local.get $5
      local.get $6
      local.get $7
      global.get $0
      i32.const  3
      i32.sub
      call $foo
      return
    )
    i32.const 0
    return
  )
  (func $baz
    (param $8 i32);;a
    (result i32)
    (block $L2
      i32.const 23
      i32.const 7
      call $prints
      global.get $0
      i32.const  1
      i32.add
      global.set $0
      local.get $8
      return
    )
    i32.const 0
    return
  )
  (start $main)
  (func $main
    (block $L3
      i32.const 30
      i32.const 8
      call $prints
      i32.const  10
      global.set $0
      i32.const  1
      i32.const  2
      i32.const  3
      call $baz
      i32.const  4
      call $bar
      i32.const  5
      i32.const  6
      call $baz
      i32.const  7
      call $bar
      i32.const  8
      call $baz
      call $foo
      call $printi
      i32.const 38
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
    (param $9 i32);;i
    (local $10 i32);;digit
    (local $11 i32);;divisor
    (local $12 i32);;remainder
    (local $13 i32);;lz
    (local $14 i32);;negative
    (block $L4
      i32.const 0;;boolean false
      local.set $14
      i32.const  0
      local.set $13
      i32.const  1000000000
      local.set $11
      local.get $9
      local.set $12
      i32.const  0
      local.set $10
      ;;if condition
      local.get $12
      i32.const  0
      i32.lt_s
      (if
        (then
          (block $L5
            i32.const  45
            call $putchar
            i32.const 1;;boolean true
            local.set $14
          )
        )
      )
      (block $L6
        (loop $L7
          ;;loop condition
          local.get $13
          i32.const  0
          i32.eq
          local.get $11
          i32.const  0
          i32.gt_s
          i32.and
          ;;loop test
          i32.eqz
          br_if $L6
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L8
            local.get $12
            local.get $11
            i32.div_s
            local.set $13
            local.get $12
            local.get $11
            i32.rem_s
            local.set $12
            local.get $11
            i32.const  10
            i32.div_s
            local.set $11
          )
          ;;finished auto generated .wasm code
          br $L7
        )
      )
      local.get $13
      local.set $10
      (block $L9
        (loop $L10
          ;;loop condition
          local.get $11
          i32.const  0
          i32.gt_s
          ;;loop test
          i32.eqz
          br_if $L9
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L11
            ;;if condition
            local.get $14
            (if
              (then
                (block $L12
                  i32.const  48
                  i32.const  0
                  local.get $10
                  i32.sub
                  i32.add
                  call $putchar
                )
              )
              (else
                (block $L13
                  i32.const  48
                  local.get $10
                  i32.add
                  call $putchar
                )
              )
            )
            local.get $12
            local.get $11
            i32.div_s
            local.set $10
            local.get $12
            local.get $11
            i32.rem_s
            local.set $12
            local.get $11
            i32.const  10
            i32.div_s
            local.set $11
          )
          ;;finished auto generated .wasm code
          br $L10
        )
      )
      ;;if condition
      local.get $14
      (if
        (then
          (block $L14
            i32.const  48
            i32.const  0
            local.get $10
            i32.sub
            i32.add
            call $putchar
          )
        )
        (else
          (block $L15
            i32.const  48
            local.get $10
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
    (param $15 i32);;b
    (block $L16
      ;;if condition
      local.get $15
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
    (param $16 i32);;c
    (block $L17
      local.get $16
      call $putchar
    )
  )
  ;;finished auto generated .wasm code
  
  (memory 1)
);;finished auto generated .wasm code
