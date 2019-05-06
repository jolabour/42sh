# 42sh

42sh is the last shell project of 42. This project aims to introduce us to the development of a shell.
It's a group project that I realized with 4 people. 
We chose to make a posix bash style shell

## compile and run

run ```make && ./42sh```

## feature required

- [x] simple command (example:```ls```)
- [x] environement variable (example:```$PATH```)
- [x] local variable (example:```a=b; echo ${a}```)
- [x] signal management (example:```CTRL-C```)
- [x] job control (example:```ls &```)
- [x] temporary variable (example:```HOME=/tmp cd```)
- [x] simple expansion (example:```echo ${PATH}```)
- [x] expansion of special parameters (example:```echo ${?}```)

###### operators

- [x] >
- [x] <
- [x] <<
- [x] >>
- [x] <&
- [x] >&
- [x] io_number
- [x] |
- [x] ||
- [x] &&
- [x] ;

###### builtins

- [x] cd
- [x] echo
- [x] exit
- [x] type
- [x] set
- [x] unset
- [x] export
- [x] jobs
- [x] fg
- [x] bg

###### line edition

- [x] ```LEFT AND RIGHT ARROWS```move cursor on the right or left. In select mode, move the select part
- [x] ```UP AND DOWN ARROWS``` move in the historic
- [x] ```DEL``` clear a character. In select mode, del the select part and exit select mode
- [x] ```HOME``` move to the beginning of the line
- [x] ```END``` move to the end of the line
- [x] ```OPT+UP``` move up
- [x] ```OPT+DOWN``` move down
- [x] ```CTRL-C``` print new prompt
- [x] ```CTRL-D``` del on the right if line in not empty otherwise leaves the shell
- [x] ```OPT-B``` move to previous word
- [x] ```OPT+F``` move to next word
- [x] ```OPT+V``` past the copy line
- [x] ```OPT+C``` enter in select mode. In select mode, copy the select part and exit select mode
- [x] ```OPT+X``` enter in select mode. In select mode, cut the select part and exit select mode

## optional feature
- [x] quoting ” (double quote), ’ (simple quote) et \ (backslash)
- [ ] pattern matching (globing) : *, ?, [], !
- [x] tilde expansions and additional formats of parameters
- [x] grouped command and subshell : (), {};
- [x] command substitution : $()
- [x] arithmetic expansion : $(())
- [ ] processus substitution : <(), >()
- [ ] complete management of the history
- [ ] dynamic completion
- [ ] Vi and Readline for the line edition
- [x] alias and unalias buitlins
- [x] hash builtin and hashtable for binary
- [x] test builtin

# final mark

**100/100**
