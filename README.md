# libhimem
HIMEM IOCS call C bridge for X68k

elf2x68k環境向けのHIMEM.SYSファンクションコールラッパーCライブラリです。

HIMEM.SYS(060turbo.SYS/TS16DRVp.X)のファンクションコールに準じた以下の関数が利用可能です。

```
#include <himem.h>

void* himem_malloc(size_t size);
void* himem_calloc(size_t count, size_t size);  // 060turbo.sys / TS16DRVp.X のみ
void himem_free(void* ptr);
size_t himem_getsize();
int32_t himem_resize(void* ptr, size_t size);
```

また、HIMEMが利用可能か確認を行う関数も利用可能です。
```
int32_t himem_isavailable(void);
```


使う時は、サブモジュールとして組み込むのが簡単です。例えばプロジェクト直下にて以下を実行します。

```
git submodule add https://github.com/tantanGH/libhimem.git libs/libhimem
```

以下のようなツリーとなります。

```
my_app/
├── .git/
├── .gitmodules
├── libs/
│   └── libhimem/
│       ├── include/himem.h
│       └── lib/libhimem.a
└── src/
    ├── main.c
    └── Makefile
```

ヘッダー検索パスとライブラリ検索パスをMakefile内で
```
-I../libs/libhimem/include
-L../libs/libhimem/lib
```
のように指定し、`-lhimem` でリンクできます。
