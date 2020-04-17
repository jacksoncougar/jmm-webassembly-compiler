;;begins auto generated .wasm code
(module
  ;;externs/imports
  (import "host" "exit" (func $halt))
  (import "host" "getchar" (func $getchar (result i32)))
  (import "host" "putchar" (func $putchar (param i32)))
  ;;data
  (data 0 (i32.const 0) "true")
  (data 0 (i32.const 4) "false")
  (data 0 (i32.const 9) "Internal error: too many ungets!\n")
  (data 0 (i32.const 43) "Error: expected ")
  (data 0 (i32.const 59) "\n")
  (data 0 (i32.const 61) "Error: invalid character.\n")
  (data 0 (i32.const 88) " = ")
  (data 0 (i32.const 91) "Error: expected factor.\n")
  (global $0 (mut i32) (i32.const 0))
  (global $1 (mut i32) (i32.const 0))
  (global $2 (mut i32) (i32.const 0))
  (global $3 (mut i32) (i32.const 0))
  (global $4 (mut i32) (i32.const 0))
  (global $5 (mut i32) (i32.const 0))
  (global $6 (mut i32) (i32.const 0))
  (global $7 (mut i32) (i32.const 0))
  (global $8 (mut i32) (i32.const 0))
  (global $9 (mut i32) (i32.const 0))
  (global $10 (mut i32) (i32.const 0))
  (global $11 (mut i32) (i32.const 0))
  (global $12 (mut i32) (i32.const 0))
  (global $13 (mut i32) (i32.const 0))
  (global $14 (mut i32) (i32.const 0))
  (global $15 (mut i32) (i32.const 0))
  (global $16 (mut i32) (i32.const 0))
  (global $17 (mut i32) (i32.const 0))
  (global $18 (mut i32) (i32.const 0))
  (global $19 (mut i32) (i32.const 0))
  (global $20 (mut i32) (i32.const 0))
  (global $21 (mut i32) (i32.const 0))
  (global $22 (mut i32) (i32.const 0))
  (global $23 (mut i32) (i32.const 0))
  (global $24 (mut i32) (i32.const 0))
  (global $25 (mut i32) (i32.const 0))
  (global $26 (mut i32) (i32.const 0))
  ;;program
  ;;begins auto generated .wasm code
  (start $main)
  (func $main
    (block $L0
      call $init
      call $parser
    )
  )
  (func $getc
    (result i32)
    (block $L1
      ;;if condition
      global.get $0
      (if
        (then
          (block $L2
            i32.const 0;;boolean false
            global.set $0
            global.get $1
            return
          )
        )
      )
      call $getchar
      return
    )
    i32.const 0
    return
  )
  (func $ungetc
    (param $27 i32);;ch
    (block $L3
      ;;if condition
      global.get $0
      (if
        (then
          (block $L4
            i32.const 9
            i32.const 34
            call $prints
            call $halt
          )
        )
      )
      i32.const 1;;boolean true
      global.set $0
      local.get $27
      global.set $1
    )
  )
  (func $peek
    (result i32)
    (block $L5
      ;;if condition
      global.get $2
      (if
        (then
          global.get $3
          return
        )
      )
      i32.const 1;;boolean true
      global.set $2
      call $scanner
      global.set $3
      global.get $3
      return
    )
    i32.const 0
    return
  )
  (func $match
    (param $28 i32);;expect
    (block $L6
      ;;if condition
      call $peek
      local.get $28
      i32.ne
      (if
        (then
          (block $L7
            i32.const 43
            i32.const 16
            call $prints
            local.get $28
            call $printc
            i32.const 59
            i32.const 2
            call $prints
            call $halt
          )
        )
      )
      i32.const 0;;boolean false
      global.set $2
    )
  )
  (func $scanner
    (result i32)
    (local $29 i32);;ch
    (block $L8
      (block $L9
        (loop $L10
          ;;loop condition
          call $getc
          local.set $29
          local.get $29
          call $isspace
          ;;loop test
          i32.eqz
          br_if $L9
          ;;loop body
          ;;begins auto generated .wasm code
          ;;finished auto generated .wasm code
          br $L10
        )
      )
      ;;if condition
      local.get $29
      global.get $5
      i32.eq
      (if
        (then
          global.get $6
          return
        )
      )
      ;;if condition
      local.get $29
      global.get $26
      i32.eq
      (if
        (then
          global.get $7
          return
        )
      )
      ;;if condition
      local.get $29
      global.get $17
      i32.eq
      (if
        (then
          global.get $9
          return
        )
      )
      ;;if condition
      local.get $29
      global.get $18
      i32.eq
      (if
        (then
          global.get $10
          return
        )
      )
      ;;if condition
      local.get $29
      global.get $19
      i32.eq
      (if
        (then
          global.get $11
          return
        )
      )
      ;;if condition
      local.get $29
      global.get $20
      i32.eq
      (if
        (then
          global.get $12
          return
        )
      )
      ;;if condition
      local.get $29
      global.get $21
      i32.eq
      (if
        (then
          global.get $13
          return
        )
      )
      ;;if condition
      local.get $29
      global.get $22
      i32.eq
      (if
        (then
          global.get $14
          return
        )
      )
      ;;if condition
      local.get $29
      call $isdigit
      (if
        (then
          (block $L11
            i32.const  0
            global.set $4
            (block $L12
              (loop $L13
                ;;loop condition
                local.get $29
                call $isdigit
                ;;loop test
                i32.eqz
                br_if $L12
                ;;loop body
                ;;begins auto generated .wasm code
                (block $L14
                  global.get $4
                  i32.const  10
                  i32.mul
                  local.get $29
                  global.get $15
                  i32.sub
                  i32.add
                  global.set $4
                  call $getc
                  local.set $29
                )
                ;;finished auto generated .wasm code
                br $L13
              )
            )
            local.get $29
            call $ungetc
            global.get $8
            return
          )
        )
      )
      i32.const 61
      i32.const 27
      call $prints
      call $halt
    )
    i32.const 0
    return
  )
  (func $isdigit
    (param $30 i32);;ch
    (result i32)
    (block $L15
      local.get $30
      global.get $15
      i32.ge_s
      local.get $30
      global.get $16
      i32.le_s
      i32.and
      return
    )
    i32.const 0
    return
  )
  (func $isspace
    (param $31 i32);;ch
    (result i32)
    (block $L16
      local.get $31
      global.get $23
      i32.eq
      local.get $31
      global.get $24
      i32.eq
      i32.or
      local.get $31
      global.get $25
      i32.eq
      i32.or
      return
    )
    i32.const 0
    return
  )
  (func $parser
    (local $32 i32);;result
    (block $L17
      (block $L18
        (loop $L19
          ;;loop condition
          call $peek
          global.get $6
          i32.ne
          ;;loop test
          i32.eqz
          br_if $L18
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L20
            call $E
            local.set $32
            global.get $7
            call $match
            i32.const 88
            i32.const 3
            call $prints
            local.get $32
            call $printi
            i32.const 59
            i32.const 2
            call $prints
          )
          ;;finished auto generated .wasm code
          br $L19
        )
      )
    )
  )
  (func $E
    (result i32)
    (local $33 i32);;l
    (local $34 i32);;r
    (local $35 i32);;token
    (block $L21
      call $T
      local.set $33
      (block $L22
        (loop $L23
          ;;loop condition
          call $peek
          global.get $9
          i32.eq
          call $peek
          global.get $10
          i32.eq
          i32.or
          ;;loop test
          i32.eqz
          br_if $L22
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L24
            call $peek
            local.set $35
            local.get $35
            call $match
            call $T
            local.set $34
            ;;if condition
            local.get $35
            global.get $9
            i32.eq
            (if
              (then
                local.get $33
                local.get $34
                i32.add
                local.set $33
              )
              (else
                local.get $33
                local.get $34
                i32.sub
                local.set $33
              )
            )
          )
          ;;finished auto generated .wasm code
          br $L23
        )
      )
      local.get $33
      return
    )
    i32.const 0
    return
  )
  (func $T
    (result i32)
    (local $36 i32);;l
    (local $37 i32);;r
    (local $38 i32);;token
    (block $L25
      call $F
      local.set $36
      (block $L26
        (loop $L27
          ;;loop condition
          call $peek
          global.get $11
          i32.eq
          call $peek
          global.get $12
          i32.eq
          i32.or
          ;;loop test
          i32.eqz
          br_if $L26
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L28
            call $peek
            local.set $38
            local.get $38
            call $match
            call $F
            local.set $37
            ;;if condition
            local.get $38
            global.get $11
            i32.eq
            (if
              (then
                local.get $36
                local.get $37
                i32.mul
                local.set $36
              )
              (else
                local.get $36
                local.get $37
                i32.div_s
                local.set $36
              )
            )
          )
          ;;finished auto generated .wasm code
          br $L27
        )
      )
      local.get $36
      return
    )
    i32.const 0
    return
  )
  (func $F
    (result i32)
    (local $39 i32);;result
    (local $40 i32);;token
    (block $L29
      call $peek
      local.set $40
      ;;if condition
      local.get $40
      global.get $13
      i32.eq
      (if
        (then
          (block $L30
            global.get $13
            call $match
            call $E
            local.set $39
            global.get $14
            call $match
          )
        )
        (else
          ;;if condition
          local.get $40
          global.get $10
          i32.eq
          (if
            (then
              (block $L31
                global.get $10
                call $match
                ;;unaryexpression negation
                call $F
                i32.const -1
                i32.xor
                i32.const 1
                i32.add
                ;;end negation
                local.set $39
              )
            )
            (else
              ;;if condition
              local.get $40
              global.get $8
              i32.eq
              (if
                (then
                  (block $L32
                    global.get $8
                    call $match
                    global.get $4
                    local.set $39
                  )
                )
                (else
                  (block $L33
                    i32.const 91
                    i32.const 25
                    call $prints
                    call $halt
                  )
                )
              )
            )
          )
        )
      )
      local.get $39
      return
    )
    i32.const 0
    return
  )
  (func $init
    (block $L34
      ;;unaryexpression negation
      i32.const  1
      i32.const -1
      i32.xor
      i32.const 1
      i32.add
      ;;end negation
      global.set $5
      i32.const  48
      global.set $15
      i32.const  57
      global.set $16
      i32.const  43
      global.set $17
      i32.const  45
      global.set $18
      i32.const  42
      global.set $19
      i32.const  47
      global.set $20
      i32.const  40
      global.set $21
      i32.const  41
      global.set $22
      i32.const  32
      global.set $23
      i32.const  9
      global.set $24
      i32.const  13
      global.set $25
      i32.const  10
      global.set $26
      i32.const  256
      global.set $6
      i32.const  257
      global.set $8
      global.get $17
      global.set $9
      global.get $18
      global.set $10
      global.get $19
      global.set $11
      global.get $20
      global.set $12
      global.get $21
      global.set $13
      global.get $22
      global.set $14
      global.get $26
      global.set $7
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
    (param $41 i32);;i
    (local $42 i32);;digit
    (local $43 i32);;divisor
    (local $44 i32);;remainder
    (local $45 i32);;lz
    (local $46 i32);;negative
    (block $L35
      i32.const 0;;boolean false
      local.set $46
      i32.const  0
      local.set $45
      i32.const  1000000000
      local.set $43
      local.get $41
      local.set $44
      i32.const  0
      local.set $42
      ;;if condition
      local.get $44
      i32.const  0
      i32.lt_s
      (if
        (then
          (block $L36
            i32.const  45
            call $putchar
            i32.const 1;;boolean true
            local.set $46
          )
        )
      )
      (block $L37
        (loop $L38
          ;;loop condition
          local.get $45
          i32.const  0
          i32.eq
          local.get $43
          i32.const  0
          i32.gt_s
          i32.and
          ;;loop test
          i32.eqz
          br_if $L37
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L39
            local.get $44
            local.get $43
            i32.div_s
            local.set $45
            local.get $44
            local.get $43
            i32.rem_s
            local.set $44
            local.get $43
            i32.const  10
            i32.div_s
            local.set $43
          )
          ;;finished auto generated .wasm code
          br $L38
        )
      )
      local.get $45
      local.set $42
      (block $L40
        (loop $L41
          ;;loop condition
          local.get $43
          i32.const  0
          i32.gt_s
          ;;loop test
          i32.eqz
          br_if $L40
          ;;loop body
          ;;begins auto generated .wasm code
          (block $L42
            ;;if condition
            local.get $46
            (if
              (then
                (block $L43
                  i32.const  48
                  i32.const  0
                  local.get $42
                  i32.sub
                  i32.add
                  call $putchar
                )
              )
              (else
                (block $L44
                  i32.const  48
                  local.get $42
                  i32.add
                  call $putchar
                )
              )
            )
            local.get $44
            local.get $43
            i32.div_s
            local.set $42
            local.get $44
            local.get $43
            i32.rem_s
            local.set $44
            local.get $43
            i32.const  10
            i32.div_s
            local.set $43
          )
          ;;finished auto generated .wasm code
          br $L41
        )
      )
      ;;if condition
      local.get $46
      (if
        (then
          (block $L45
            i32.const  48
            i32.const  0
            local.get $42
            i32.sub
            i32.add
            call $putchar
          )
        )
        (else
          (block $L46
            i32.const  48
            local.get $42
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
    (param $47 i32);;b
    (block $L47
      ;;if condition
      local.get $47
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
    (param $48 i32);;c
    (block $L48
      local.get $48
      call $putchar
    )
  )
  ;;finished auto generated .wasm code
  
  (memory 1)
);;finished auto generated .wasm code
