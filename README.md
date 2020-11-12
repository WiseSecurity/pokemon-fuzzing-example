# pokemon-fuzzing-example

Fuzz with Pokemon! (TM)

#### Binary building (i.e. with AFL++ & honggfuzz)
```
AFL_USE_ASAN=1 afl-clang-fast -g pokemon_dirty.c -o pokemon_dirty
hfuzz-clang -g pokemon_dirty.c -o pokemon_dirty
```

#### Raw fuzzing
```
afl-fuzz -i pokemon_copora/ -o pokemon_output/ -- ./pokemon_dirty @@
honggfuzz -i pokemon_corpora/ -o pokemon_out/ -W pokemon_crashes/ -- ./pokemon_dirty ___FILE___
```

#### Fuzzing with dictionary
```
afl-fuzz -i pokemon_copora/ -o pokemon_output/ -x pokemon.dict -- ./pokemon_dirty @@
honggfuzz -i pokemon_corpora/ -o pokemon_out/ -W pokemon_crashes/ -w pokemon.dict -- ./pokemon_dirty ___FILE___
```

#### Results (AFL++ & honggfuzz)

+ AFL++
```
                american fuzzy lop ++3.00a (f01) [explore] {0}
┌─ process timing ────────────────────────────────────┬─ overall results ────┐
│        run time : 0 days, 0 hrs, 0 min, 12 sec      │  cycles done : 39    │
│   last new path : none yet (odd, check syntax!)     │  total paths : 2     │
│ last uniq crash : 0 days, 0 hrs, 0 min, 12 sec      │ uniq crashes : 2     │
│  last uniq hang : none seen yet                     │   uniq hangs : 0     │
├─ cycle progress ───────────────────┬─ map coverage ─┴──────────────────────┤
│  now processing : 0.39 (0.0%)      │    map density : 12.50% / 12.50%      │
│ paths timed out : 0 (0.00%)        │ count coverage : 1.00 bits/tuple      │
├─ stage progress ───────────────────┼─ findings in depth ───────────────────┤
│  now trying : havoc                │ favored paths : 1 (50.00%)            │
│ stage execs : 190/512 (37.11%)     │  new edges on : 1 (50.00%)            │
│ total execs : 24.6k                │ total crashes : 222 (2 unique)        │
│  exec speed : 1911/sec             │  total tmouts : 0 (0 unique)          │
├─ fuzzing strategy yields ──────────┴───────────────┬─ path geometry ───────┤
│   bit flips : 0/32, 0/31, 0/29                     │    levels : 1         │
│  byte flips : 0/4, 0/3, 0/1                        │   pending : 0         │
│ arithmetics : 0/223, 0/0, 0/0                      │  pend fav : 0         │
│  known ints : 0/21, 0/84, 0/44                     │ own finds : 0         │
│  dictionary : 0/0, 2/125, 0/0                      │  imported : 0         │
│havoc/splice : 0/23.8k, 0/0                         │ stability : 100.00%   │
│   py/custom : 0/0, 0/0                             ├───────────────────────┘
│        trim : 20.00%/1, 0.00%                      │          [cpu000: 25%]
└────────────────────────────────────────────────────┘
```
+ honggfuzz
```

------------------------[  0 days 00 hrs 00 mins 05 secs ]----------------------
  Iterations : 10,095 [10.10k]
  Mode [3/3] : Feedback Driven Mode
      Target : ./pokemon_dirty ___FILE___
     Threads : 4, CPUs: 8, CPU%: 435% [54%/CPU]
       Speed : 2,115/sec [avg: 2,019]
     Crashes : 273 [unique: 273, blacklist: 0, verified: 0]
    Timeouts : 0 [1 sec]
 Corpus Size : 28, max: 8,192 bytes, init: 1 files
  Cov Update : 0 days 00 hrs 00 mins 01 secs ago
    Coverage : edge: 8/11 [72%] pc: 2 cmp: 188
---------------------------------- [ LOGS ] ------------------/ honggfuzz 2.3 /-
x.fuzz'
Crash: saved as 'pokemon_crashes/SIGABRT.PC.7f350098e18b.STACK.1b4fcde3f1.CODE.-6.ADDR.0.INSTR.mov____0x108(%rsp),%ra
x.fuzz'
Crash: saved as 'pokemon_crashes/SIGABRT.PC.7fa7c9ebd18b.STACK.1b4fcde3f1.CODE.-6.ADDR.0.INSTR.mov____0x108(%rsp),%ra
x.fuzz'
Crash: saved as 'pokemon_crashes/SIGABRT.PC.7f9cb1d8c18b.STACK.1b4fcde3f1.CODE.-6.ADDR.0.INSTR.mov____0x108(%rsp),%ra
x.fuzz'
Signal 2 (Interrupt) received, terminating
Terminating thread no. #2, left: 3
Crash: saved as 'pokemon_crashes/SIGABRT.PC.7fb565ac718b.STACK.1b4fcde3f1.CODE.-6.ADDR.0.INSTR.mov____0x108(%rsp),%ra
x.fuzz'
Terminating thread no. #1, left: 2
Terminating thread no. #3, left: 1
Terminating thread no. #0, left: 0
Summary iterations:10098 time:5 speed:2019 crashes_count:274 timeout_count:0 new_units_added:25 slowest_unit_ms:12 gu
ard_nb:11 branch_coverage_percent:72 peak_rss_mb:12
```
