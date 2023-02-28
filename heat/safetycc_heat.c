struct _IO_FILE_plus;
extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
struct _IO_FILE;
extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;
extern int sys_nerr;
extern const char *const sys_errlist[];
typedef struct _IO_FILE _IO_FILE;
extern int _IO_getc(_IO_FILE *__fp);
extern struct _IO_FILE *stdin;
extern __inline __attribute__((__gnu_inline__)) int getchar(void)
{
  return _IO_getc(stdin);
}
typedef struct _IO_FILE FILE;
struct _IO_marker;
typedef long int __off_t;
typedef void _IO_lock_t;
typedef long int __off64_t;
typedef unsigned long int size_t;
struct  _IO_FILE
{
  int _flags;
  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2;
  __off_t _old_offset;
  unsigned short int _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1L];
  _IO_lock_t *_lock;
  __off64_t _offset;
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;
  int _mode;
  char _unused2[20L];
};
extern int __uflow(_IO_FILE *);
extern __inline __attribute__((__gnu_inline__)) int fgetc_unlocked(FILE *__fp)
{
  return __builtin_expect((*__fp)._IO_read_ptr >= (*__fp)._IO_read_end, 0) ? __uflow(__fp) : *((unsigned char *)(*__fp)._IO_read_ptr++);
}
extern __inline __attribute__((__gnu_inline__)) int getc_unlocked(FILE *__fp)
{
  return __builtin_expect((*__fp)._IO_read_ptr >= (*__fp)._IO_read_end, 0) ? __uflow(__fp) : *((unsigned char *)(*__fp)._IO_read_ptr++);
}
extern __inline __attribute__((__gnu_inline__)) int getchar_unlocked(void)
{
  return __builtin_expect((*stdin)._IO_read_ptr >= (*stdin)._IO_read_end, 0) ? __uflow(stdin) : *((unsigned char *)(*stdin)._IO_read_ptr++);
}
extern int _IO_putc(int __c, _IO_FILE *__fp);
extern struct _IO_FILE *stdout;
extern __inline __attribute__((__gnu_inline__)) int putchar(int __c)
{
  return _IO_putc(__c, stdout);
}
extern int __overflow(_IO_FILE *, int);
extern __inline __attribute__((__gnu_inline__)) int fputc_unlocked(int __c, FILE *__stream)
{
  return __builtin_expect((*__stream)._IO_write_ptr >= (*__stream)._IO_write_end, 0) ? __overflow(__stream, (unsigned char)__c) : (unsigned char)(*(*__stream)._IO_write_ptr++ = __c);
}
extern __inline __attribute__((__gnu_inline__)) int putc_unlocked(int __c, FILE *__stream)
{
  return __builtin_expect((*__stream)._IO_write_ptr >= (*__stream)._IO_write_end, 0) ? __overflow(__stream, (unsigned char)__c) : (unsigned char)(*(*__stream)._IO_write_ptr++ = __c);
}
extern __inline __attribute__((__gnu_inline__)) int putchar_unlocked(int __c)
{
  return __builtin_expect((*stdout)._IO_write_ptr >= (*stdout)._IO_write_end, 0) ? __overflow(stdout, (unsigned char)__c) : (unsigned char)(*(*stdout)._IO_write_ptr++ = __c);
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__warn_unused_result__)) __attribute__((__gnu_inline__)) int feof_unlocked(FILE *__stream)
{
  return ((*__stream)._flags & 16) != 0;
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__warn_unused_result__)) __attribute__((__gnu_inline__)) int ferror_unlocked(FILE *__stream)
{
  return ((*__stream)._flags & 32) != 0;
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int sprintf(char *__restrict __s, const char *__restrict __fmt, ...)
{
  return __builtin___sprintf_chk(__s, 2 - 1, __builtin_object_size(__s, 2 > 1), __fmt, __builtin_va_arg_pack());
}
typedef __builtin_va_list __gnuc_va_list;
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int vsprintf(char *__restrict __s, const char *__restrict __fmt, __gnuc_va_list __ap)
{
  return __builtin___vsprintf_chk(__s, 2 - 1, __builtin_object_size(__s, 2 > 1), __fmt, __ap);
}
extern __inline __attribute__((__nothrow__)) __attribute__((__format__(__printf__, 3, 4))) __attribute__((__leaf__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int snprintf(char *__restrict __s, size_t __n, const char *__restrict __fmt, ...)
{
  return __builtin___snprintf_chk(__s, __n, 2 - 1, __builtin_object_size(__s, 2 > 1), __fmt, __builtin_va_arg_pack());
}
extern __inline __attribute__((__nothrow__)) __attribute__((__format__(__printf__, 3, 0))) __attribute__((__leaf__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int vsnprintf(char *__restrict __s, size_t __n, const char *__restrict __fmt, __gnuc_va_list __ap)
{
  return __builtin___vsnprintf_chk(__s, __n, 2 - 1, __builtin_object_size(__s, 2 > 1), __fmt, __ap);
}
extern int __fprintf_chk(FILE *__restrict __stream, int __flag, const char *__restrict __format, ...);
extern __inline __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int fprintf(FILE *__restrict __stream, const char *__restrict __fmt, ...)
{
  return __fprintf_chk(__stream, 2 - 1, __fmt, __builtin_va_arg_pack());
}
extern int __printf_chk(int __flag, const char *__restrict __format, ...);
extern __inline __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int printf(const char *__restrict __fmt, ...)
{
  return __printf_chk(2 - 1, __fmt, __builtin_va_arg_pack());
}
extern int __vfprintf_chk(FILE *__restrict __stream, int __flag, const char *__restrict __format, __gnuc_va_list __ap);
extern __inline __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int vprintf(const char *__restrict __fmt, __gnuc_va_list __ap)
{
  return __vfprintf_chk(stdout, 2 - 1, __fmt, __ap);
}
extern __inline __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int vfprintf(FILE *__restrict __stream, const char *__restrict __fmt, __gnuc_va_list __ap)
{
  return __vfprintf_chk(__stream, 2 - 1, __fmt, __ap);
}
extern int __dprintf_chk(int __fd, int __flag, const char *__restrict __fmt, ...) __attribute__((__format__(__printf__, 3, 4)));
extern __inline __attribute__((__format__(__printf__, 2, 3))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int dprintf(int __fd, const char *__restrict __fmt, ...)
{
  return __dprintf_chk(__fd, 2 - 1, __fmt, __builtin_va_arg_pack());
}
extern int __vdprintf_chk(int __fd, int __flag, const char *__restrict __fmt, __gnuc_va_list __arg) __attribute__((__format__(__printf__, 3, 0)));
extern __inline __attribute__((__format__(__printf__, 2, 0))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int vdprintf(int __fd, const char *__restrict __fmt, __gnuc_va_list __ap)
{
  return __vdprintf_chk(__fd, 2 - 1, __fmt, __ap);
}
extern char *__gets_chk(char *__str, size_t) __attribute__((__warn_unused_result__));
extern char *__gets_warn(char *__str) __asm("""gets") __attribute__((__warn_unused_result__)) __attribute__((__warning__("please use fgets or getline instead, gets can't ""specify buffer size")));
extern __inline __attribute__((__warn_unused_result__)) __attribute__((__deprecated__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) char *gets(char *__str)
{
  if (__builtin_object_size(__str, 2 > 1) != (size_t) -1)
    {
      return __gets_chk(__str, __builtin_object_size(__str, 2 > 1));
    }
  return __gets_warn(__str);
}
extern char *__fgets_chk(char *__restrict __s, size_t __size, int __n, FILE *__restrict __stream) __attribute__((__warn_unused_result__));
extern char *__fgets_chk_warn(char *__restrict __s, size_t __size, int __n, FILE *__restrict __stream) __asm("""__fgets_chk") __attribute__((__warn_unused_result__)) __attribute__((__warning__("fgets called with bigger size than length ""of destination buffer")));
extern char *__fgets_alias(char *__restrict __s, int __n, FILE *__restrict __stream) __asm("""fgets") __attribute__((__warn_unused_result__));
extern __inline __attribute__((__warn_unused_result__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) char *fgets(char *__restrict __s, int __n, FILE *__restrict __stream)
{
  if (__builtin_object_size(__s, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p(__n) || __n <= 0)
        {
          return __fgets_chk(__s, __builtin_object_size(__s, 2 > 1), __n, __stream);
        }
      if ((size_t)__n > __builtin_object_size(__s, 2 > 1))
        {
          return __fgets_chk_warn(__s, __builtin_object_size(__s, 2 > 1), __n, __stream);
        }
    }
  return __fgets_alias(__s, __n, __stream);
}
extern size_t __fread_chk(void *__restrict __ptr, size_t __ptrlen, size_t __size, size_t __n, FILE *__restrict __stream) __attribute__((__warn_unused_result__));
extern size_t __fread_chk_warn(void *__restrict __ptr, size_t __ptrlen, size_t __size, size_t __n, FILE *__restrict __stream) __asm("""__fread_chk") __attribute__((__warn_unused_result__)) __attribute__((__warning__("fread called with bigger size * nmemb than length ""of destination buffer")));
extern size_t __fread_alias(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) __asm("""fread") __attribute__((__warn_unused_result__));
extern __inline __attribute__((__warn_unused_result__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) size_t fread(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream)
{
  if (__builtin_object_size(__ptr, 0) != (size_t) -1)
    {
      if ((!__builtin_constant_p(__size) || !__builtin_constant_p(__n)) || (__size | __n) >= (size_t)1 << 8 * sizeof(size_t) / 2)
        {
          return __fread_chk(__ptr, __builtin_object_size(__ptr, 0), __size, __n, __stream);
        }
      if (__size * __n > __builtin_object_size(__ptr, 0))
        {
          return __fread_chk_warn(__ptr, __builtin_object_size(__ptr, 0), __size, __n, __stream);
        }
    }
  return __fread_alias(__ptr, __size, __n, __stream);
}
extern size_t __fread_unlocked_chk(void *__restrict __ptr, size_t __ptrlen, size_t __size, size_t __n, FILE *__restrict __stream) __attribute__((__warn_unused_result__));
extern size_t __fread_unlocked_chk_warn(void *__restrict __ptr, size_t __ptrlen, size_t __size, size_t __n, FILE *__restrict __stream) __asm("""__fread_unlocked_chk") __attribute__((__warn_unused_result__)) __attribute__((__warning__("fread_unlocked called with bigger size * nmemb than ""length of destination buffer")));
extern size_t __fread_unlocked_alias(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream) __asm("""fread_unlocked") __attribute__((__warn_unused_result__));
extern __inline __attribute__((__warn_unused_result__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) size_t fread_unlocked(void *__restrict __ptr, size_t __size, size_t __n, FILE *__restrict __stream)
{
  if (__builtin_object_size(__ptr, 0) != (size_t) -1)
    {
      if ((!__builtin_constant_p(__size) || !__builtin_constant_p(__n)) || (__size | __n) >= (size_t)1 << 8 * sizeof(size_t) / 2)
        {
          return __fread_unlocked_chk(__ptr, __builtin_object_size(__ptr, 0), __size, __n, __stream);
        }
      if (__size * __n > __builtin_object_size(__ptr, 0))
        {
          return __fread_unlocked_chk_warn(__ptr, __builtin_object_size(__ptr, 0), __size, __n, __stream);
        }
    }
  if (((__builtin_constant_p(__size) && __builtin_constant_p(__n)) && (__size | __n) < (size_t)1 << 8 * sizeof(size_t) / 2) && __size * __n <= 8)
    {
      size_t __cnt = __size * __n;
      char *__cptr = (char *)__ptr;
      if (__cnt == 0)
        {
          return 0;
        }
      for (; __cnt > 0;  --__cnt)
        {
          int __c = __builtin_expect((*__stream)._IO_read_ptr >= (*__stream)._IO_read_end, 0) ? __uflow(__stream) : *((unsigned char *)(*__stream)._IO_read_ptr++);
          if (__c ==  -1)
            {
              break;
            }
          *__cptr++ = __c;
        }
      return (__cptr - (char *)__ptr) / __size;
    }
  return __fread_unlocked_alias(__ptr, __size, __n, __stream);
}
extern long int strtol(const char *__restrict __nptr, char **__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1)));
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__pure__)) __attribute__((__nonnull__(1))) __attribute__((__warn_unused_result__)) __attribute__((__gnu_inline__)) int atoi(const char *__nptr)
{
  return (int)strtol(__nptr, (char **)(void *)0, 10);
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__pure__)) __attribute__((__nonnull__(1))) __attribute__((__warn_unused_result__)) __attribute__((__gnu_inline__)) long int atol(const char *__nptr)
{
  return strtol(__nptr, (char **)(void *)0, 10);
}
extern long long int strtoll(const char *__restrict __nptr, char **__restrict __endptr, int __base) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1)));
__extension__ extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__pure__)) __attribute__((__nonnull__(1))) __attribute__((__warn_unused_result__)) __attribute__((__gnu_inline__)) long long int atoll(const char *__nptr)
{
  return strtoll(__nptr, (char **)(void *)0, 10);
}
static __inline unsigned int __bswap_32(unsigned int __bsx)
{
  return __builtin_bswap32(__bsx);
}
typedef unsigned long int __uint64_t;
static __inline __uint64_t __bswap_64(__uint64_t __bsx)
{
  return __builtin_bswap64(__bsx);
}
typedef unsigned short int __uint16_t;
static __inline __uint16_t __uint16_identity(__uint16_t __x)
{
  return __x;
}
typedef unsigned int __uint32_t;
static __inline __uint32_t __uint32_identity(__uint32_t __x)
{
  return __x;
}
static __inline __uint64_t __uint64_identity(__uint64_t __x)
{
  return __x;
}
typedef unsigned long int __dev_t;
__extension__ extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__const__)) __attribute__((__gnu_inline__)) unsigned int gnu_dev_major(__dev_t __dev)
{
  __extension__ unsigned int __major;
  __major = (__dev & (__dev_t)1048320U) >> 8;
  __major |= (__dev & (__dev_t)18446726481523507200LU) >> 32;
  return __major;
}
__extension__ extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__const__)) __attribute__((__gnu_inline__)) unsigned int gnu_dev_minor(__dev_t __dev)
{
  __extension__ unsigned int __minor;
  __minor = (__dev & (__dev_t)255U) >> 0;
  __minor |= (__dev & (__dev_t)17592184995840LU) >> 12;
  return __minor;
}
__extension__ extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__const__)) __attribute__((__gnu_inline__)) __dev_t gnu_dev_makedev(unsigned int __major, unsigned int __minor)
{
  __extension__ __dev_t __dev;
  __dev = (__dev_t)(__major & 4095U) << 8;
  __dev |= (__dev_t)(__major & 4294963200U) << 32;
  __dev |= (__dev_t)(__minor & 255U) << 0;
  __dev |= (__dev_t)(__minor & 4294967040U) << 12;
  return __dev;
}
typedef int (*__compar_fn_t)(const void *, const void *);
extern __inline __attribute__((__nonnull__(1, 2, 5))) __attribute__((__warn_unused_result__)) __attribute__((__gnu_inline__)) void *bsearch(const void *__key, const void *__base, size_t __nmemb, size_t __size, __compar_fn_t __compar)
{
  size_t __l;
  size_t __u;
  size_t __idx;
  const void *__p;
  int __comparison;
  __l = 0;
  __u = __nmemb;
  while (__l < __u)
    {
      __idx = (__l + __u) / 2;
      __p = (void *)((const char *)__base + __idx * __size);
      __comparison = (*__compar)(__key, __p);
      if (__comparison < 0)
        {
          __u = __idx;
        }
      else
        {
          if (__comparison > 0)
            {
              __l = __idx + 1;
            }
          else
            {
              return (void *)__p;
            }
        }
    }
  return (void *)0;
}
extern double strtod(const char *__restrict __nptr, char **__restrict __endptr) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1)));
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__pure__)) __attribute__((__nonnull__(1))) __attribute__((__warn_unused_result__)) __attribute__((__gnu_inline__)) double atof(const char *__nptr)
{
  return strtod(__nptr, (char **)(void *)0);
}
extern char *__realpath_chk(const char *__restrict __name, char *__restrict __resolved, size_t __resolvedlen) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__warn_unused_result__));
extern char *__realpath_alias(const char *__restrict __name, char *__restrict __resolved) __asm("""realpath") __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__warn_unused_result__));
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__warn_unused_result__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) char *__attribute__((__leaf__)) realpath(const char *__restrict __name, char *__restrict __resolved)
{
  if (__builtin_object_size(__resolved, 2 > 1) != (size_t) -1)
    {
      return __realpath_chk(__name, __resolved, __builtin_object_size(__resolved, 2 > 1));
    }
  return __realpath_alias(__name, __resolved);
}
extern int __ptsname_r_chk(int __fd, char *__buf, size_t __buflen, size_t __nreal) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(2)));
extern int __ptsname_r_chk_warn(int __fd, char *__buf, size_t __buflen, size_t __nreal) __asm("""__ptsname_r_chk") __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(2))) __attribute__((__warning__("ptsname_r called with buflen bigger than ""size of buf")));
extern int __ptsname_r_alias(int __fd, char *__buf, size_t __buflen) __asm("""ptsname_r") __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(2)));
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) int ptsname_r(int __fd, char *__buf, size_t __buflen)
{
  if (__builtin_object_size(__buf, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p(__buflen))
        {
          return __ptsname_r_chk(__fd, __buf, __buflen, __builtin_object_size(__buf, 2 > 1));
        }
      if (__buflen > __builtin_object_size(__buf, 2 > 1))
        {
          return __ptsname_r_chk_warn(__fd, __buf, __buflen, __builtin_object_size(__buf, 2 > 1));
        }
    }
  return __ptsname_r_alias(__fd, __buf, __buflen);
}
typedef int wchar_t;
extern int __wctomb_chk(char *__s, wchar_t __wchar, size_t __buflen) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__warn_unused_result__));
extern int __wctomb_alias(char *__s, wchar_t __wchar) __asm("""wctomb") __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__warn_unused_result__));
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) __attribute__((__warn_unused_result__)) int wctomb(char *__s, wchar_t __wchar)
{
  if (__builtin_object_size(__s, 2 > 1) != (size_t) -1 && 16 > __builtin_object_size(__s, 2 > 1))
    {
      return __wctomb_chk(__s, __wchar, __builtin_object_size(__s, 2 > 1));
    }
  return __wctomb_alias(__s, __wchar);
}
extern size_t __mbstowcs_chk(wchar_t *__restrict __dst, const char *__restrict __src, size_t __len, size_t __dstlen) __attribute__((__nothrow__)) __attribute__((__leaf__));
extern size_t __mbstowcs_chk_warn(wchar_t *__restrict __dst, const char *__restrict __src, size_t __len, size_t __dstlen) __asm("""__mbstowcs_chk") __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__warning__("mbstowcs called with dst buffer smaller than len ""* sizeof (wchar_t)")));
extern size_t __mbstowcs_alias(wchar_t *__restrict __dst, const char *__restrict __src, size_t __len) __asm("""mbstowcs") __attribute__((__nothrow__)) __attribute__((__leaf__));
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) size_t mbstowcs(wchar_t *__restrict __dst, const char *__restrict __src, size_t __len)
{
  if (__builtin_object_size(__dst, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p(__len))
        {
          return __mbstowcs_chk(__dst, __src, __len, __builtin_object_size(__dst, 2 > 1) / sizeof(wchar_t));
        }
      if (__len > __builtin_object_size(__dst, 2 > 1) / sizeof(wchar_t))
        {
          return __mbstowcs_chk_warn(__dst, __src, __len, __builtin_object_size(__dst, 2 > 1) / sizeof(wchar_t));
        }
    }
  return __mbstowcs_alias(__dst, __src, __len);
}
extern size_t __wcstombs_chk(char *__restrict __dst, const wchar_t *__restrict __src, size_t __len, size_t __dstlen) __attribute__((__nothrow__)) __attribute__((__leaf__));
extern size_t __wcstombs_chk_warn(char *__restrict __dst, const wchar_t *__restrict __src, size_t __len, size_t __dstlen) __asm("""__wcstombs_chk") __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__warning__("wcstombs called with dst buffer smaller than len")));
extern size_t __wcstombs_alias(char *__restrict __dst, const wchar_t *__restrict __src, size_t __len) __asm("""wcstombs") __attribute__((__nothrow__)) __attribute__((__leaf__));
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) size_t wcstombs(char *__restrict __dst, const wchar_t *__restrict __src, size_t __len)
{
  if (__builtin_object_size(__dst, 2 > 1) != (size_t) -1)
    {
      if (!__builtin_constant_p(__len))
        {
          return __wcstombs_chk(__dst, __src, __len, __builtin_object_size(__dst, 2 > 1));
        }
      if (__len > __builtin_object_size(__dst, 2 > 1))
        {
          return __wcstombs_chk_warn(__dst, __src, __len, __builtin_object_size(__dst, 2 > 1));
        }
    }
  return __wcstombs_alias(__dst, __src, __len);
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1, 2))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) void bcopy(const void *__src, void *__dest, size_t __len)
{
  (void)__builtin___memmove_chk(__dest, __src, __len, __builtin_object_size(__dest, 0));
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) void bzero(void *__dest, size_t __len)
{
  (void)__builtin___memset_chk(__dest, '\000', __len, __builtin_object_size(__dest, 0));
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1, 2))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) void *__attribute__((__leaf__)) memcpy(void *__restrict __dest, const void *__restrict __src, size_t __len)
{
  return __builtin___memcpy_chk(__dest, __src, __len, __builtin_object_size(__dest, 0));
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1, 2))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) void *__attribute__((__leaf__)) memmove(void *__dest, const void *__src, size_t __len)
{
  return __builtin___memmove_chk(__dest, __src, __len, __builtin_object_size(__dest, 0));
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) void *__attribute__((__leaf__)) memset(void *__dest, int __ch, size_t __len)
{
  return __builtin___memset_chk(__dest, __ch, __len, __builtin_object_size(__dest, 0));
}
void __explicit_bzero_chk(void *__dest, size_t __len, size_t __destlen) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1)));
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) void explicit_bzero(void *__dest, size_t __len)
{
  __explicit_bzero_chk(__dest, __len, __builtin_object_size(__dest, 0));
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1, 2))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) char *__attribute__((__leaf__)) strcpy(char *__restrict __dest, const char *__restrict __src)
{
  return __builtin___strcpy_chk(__dest, __src, __builtin_object_size(__dest, 2 > 1));
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1, 2))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) char *__attribute__((__leaf__)) strncpy(char *__restrict __dest, const char *__restrict __src, size_t __len)
{
  return __builtin___strncpy_chk(__dest, __src, __len, __builtin_object_size(__dest, 2 > 1));
}
extern char *__stpncpy_chk(char *__dest, const char *__src, size_t __n, size_t __destlen) __attribute__((__nothrow__)) __attribute__((__leaf__));
extern char *__stpncpy_alias(char *__dest, const char *__src, size_t __n) __asm("""stpncpy") __attribute__((__nothrow__)) __attribute__((__leaf__));
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1, 2))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) char *__attribute__((__leaf__)) stpncpy(char *__dest, const char *__src, size_t __n)
{
  if (__builtin_object_size(__dest, 2 > 1) != (size_t) -1 && (!__builtin_constant_p(__n) || __n > __builtin_object_size(__dest, 2 > 1)))
    {
      return __stpncpy_chk(__dest, __src, __n, __builtin_object_size(__dest, 2 > 1));
    }
  return __stpncpy_alias(__dest, __src, __n);
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1, 2))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) char *__attribute__((__leaf__)) strcat(char *__restrict __dest, const char *__restrict __src)
{
  return __builtin___strcat_chk(__dest, __src, __builtin_object_size(__dest, 2 > 1));
}
extern __inline __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__nonnull__(1, 2))) __attribute__((__always_inline__)) __attribute__((__gnu_inline__)) __attribute__((__artificial__)) char *__attribute__((__leaf__)) strncat(char *__restrict __dest, const char *__restrict __src, size_t __len)
{
  return __builtin___strncat_chk(__dest, __src, __len, __builtin_object_size(__dest, 2 > 1));
}
extern char *__tzname[2L];
extern int __daylight;
extern long int __timezone;
extern char *tzname[2L];
extern int daylight;
extern long int timezone;
double **u;
extern struct _IO_FILE *stderr;
void usage(char *s)
{
  fprintf(stderr, "Usage: %s <input file> [result file]\n\n", s);
}
struct gomp_ol_args_0_t;
struct  gomp_ol_args_0_t
{
  unsigned int sizex;
  unsigned int sizey;
  double **u;
  int inf_i;
  int sup_i;
  int inf_j;
  int sup_j;
  int bx;
  int by;
};
static void _ol_relax_gauss_0(struct gomp_ol_args_0_t *ol_data_0)
{
  unsigned int sizey = (*ol_data_0).sizey;
  double **u = (*ol_data_0).u;
  int inf_i = (*ol_data_0).inf_i;
  int sup_i = (*ol_data_0).sup_i;
  int inf_j = (*ol_data_0).inf_j;
  int sup_j = (*ol_data_0).sup_j;
  {
    const long int mcc_vla_3 = sizey;
    double (*u2)[sizey] = (double (*)[mcc_vla_3])u;
    for (int i = inf_i; i < sup_i;  ++i)
      {
        for (int j = inf_j; j < sup_j;  ++j)
          {
            double unew;
            unew = 2.50000000000000000000000000000000000000000000000000000e-01 * (u2[i][j - 1] + u2[i][j + 1] + u2[i - 1][j] + u2[i + 1][j]);
            u2[i][j] = unew;
          }
      }
  }
  ;
}
enum GOMP_dep_check
{
  GOMP_DYNAMIC_TDG = 1,
  GOMP_STATIC_TDG = 2
};
extern void GOMP_task(void (*)(void *), void *, void (*)(void *, void *), long int, long int, _Bool, unsigned int, void **, int, unsigned int, unsigned int, enum GOMP_dep_check);
double relax_gauss(double *u1, unsigned int sizex, unsigned int sizey)
{
  int nbx;
  int nby;
  int bx;
  int by;
  double sum = 0.00000000000000000000000000000000000000000000000000000e+00;
  const long int mcc_vla_1 = sizey;
  u = (double (*)[mcc_vla_1])u1;
  nbx = 64;
  nby = 64;
  bx = sizex / nbx;
  by = sizey / nby;
  for (int ii = 0; ii < nbx; ii++)
    {
      for (int jj = 0; jj < nby; jj++)
        {
          struct gomp_ol_args_0_t ol_data_0;
          int inf_i = 1 + ii * bx;
          int sup_i = inf_i + bx < sizex - 1 ? inf_i + bx : sizex - 1;
          int inf_j = 1 + jj * by;
          int sup_j = inf_j + by < sizey - 1 ? inf_j + by : sizey - 1;
          ol_data_0.sizex = sizex;
          ol_data_0.sizey = sizey;
          ol_data_0.u = u;
          ol_data_0.inf_i = inf_i;
          ol_data_0.sup_i = sup_i;
          ol_data_0.inf_j = inf_j;
          ol_data_0.sup_j = sup_j;
          ol_data_0.bx = bx;
          ol_data_0.by = by;
          unsigned long int gomp_task_flags_0 = 0;
          unsigned int _gomp_task_instance_id_0 = 0;
          GOMP_task((void (*)(void *))_ol_relax_gauss_0, &ol_data_0, (void (*)(void *, void *))0, 40, 8, 1, gomp_task_flags_0, 0, 0, 1U, _gomp_task_instance_id_0, GOMP_STATIC_TDG);
        }
    }
  return sum;
}
struct gomp_ol_args_1_t;
struct  gomp_ol_args_1_t
{
  int sizex;
  int sizey;
  double **u;
  int inf_i;
  int sup_i;
  int inf_j;
  int sup_j;
  int bx;
  int by;
};
static void _ol_main_1(struct gomp_ol_args_1_t *ol_data_1)
{
  int sizey = (*ol_data_1).sizey;
  double **u = (*ol_data_1).u;
  int inf_i = (*ol_data_1).inf_i;
  int sup_i = (*ol_data_1).sup_i;
  int inf_j = (*ol_data_1).inf_j;
  int sup_j = (*ol_data_1).sup_j;
  {
    const long int mcc_vla_11 = sizey;
    double (*u2)[sizey] = (double (*)[mcc_vla_11])u;
    for (int i = inf_i; i < sup_i;  ++i)
      {
        for (int j = inf_j; j < sup_j;  ++j)
          {
            double unew;
            unew = 2.50000000000000000000000000000000000000000000000000000e-01 * (u2[i][j - 1] + u2[i][j + 1] + u2[i - 1][j] + u2[i + 1][j]);
            u2[i][j] = unew;
          }
      }
  }
  ;
}
struct gomp_ol_args_2_t;
struct mcc_struct_anon_6;
typedef struct mcc_struct_anon_6 algoparam_t;
struct  gomp_ol_args_2_t
{
  int nbx;
  int nby;
  int bx;
  int sizex;
  int by;
  int sizey;
  unsigned int *iter;
  algoparam_t *param;
  int *np;
  double ***u;
};
struct mcc_struct_anon_5;
typedef struct mcc_struct_anon_5 heatsrc_t;
struct  mcc_struct_anon_6
{
  unsigned int maxiter;
  unsigned int resolution;
  int algorithm;
  unsigned int visres;
  double *u;
  double *uhelp;
  double *uvis;
  unsigned int numsrcs;
  heatsrc_t *heatsrcs;
};
enum GOMP_task_flags
{
  GOMP_TASK_UNTIED = 1,
  GOMP_TASK_FINAL = 2,
  GOMP_TASK_MERGEABLE = 4,
  GOMP_TASK_DEPEND = 8
};
static void _ol_main_2(struct gomp_ol_args_2_t *ol_data_2)
{
  unsigned int *const iter = &(*(*ol_data_2).iter);
  algoparam_t *const param = &(*(*ol_data_2).param);
  int *const np = &(*(*ol_data_2).np);
  int nbx = (*ol_data_2).nbx;
  int nby = (*ol_data_2).nby;
  int bx = (*ol_data_2).bx;
  int sizex = (*ol_data_2).sizex;
  int by = (*ol_data_2).by;
  int sizey = (*ol_data_2).sizey;
  double ***const u = &(*(*ol_data_2).u);
  {
    unsigned int _gomp_iter_0 = 0;
    for ((*iter) = 0; (*iter) < (*param).maxiter;  ++(*iter))
      {
         ++_gomp_iter_0;
        relax_gauss((*param).u, (*np), (*np));
        unsigned int _gomp_iter_1 = 0;
        for (int ii = 0; ii < nbx; ii++)
          {
             ++_gomp_iter_1;
            unsigned int _gomp_iter_2 = 0;
            for (int jj = 0; jj < nby; jj++)
              {
                struct gomp_ol_args_1_t ol_data_1;
                 ++_gomp_iter_2;
                int inf_i = 1 + ii * bx;
                int sup_i = inf_i + bx < sizex - 1 ? inf_i + bx : sizex - 1;
                int inf_j = 1 + jj * by;
                int sup_j = inf_j + by < sizey - 1 ? inf_j + by : sizey - 1;
                ol_data_1.sizex = sizex;
                ol_data_1.sizey = sizey;
                ol_data_1.u = (*u);
                ol_data_1.inf_i = inf_i;
                ol_data_1.sup_i = sup_i;
                ol_data_1.inf_j = inf_j;
                ol_data_1.sup_j = sup_j;
                ol_data_1.bx = bx;
                ol_data_1.by = by;
                void *gomp_task_deps_1[7L] = {[0] = (void *)5U, [1] = (void *)1U, [2] = (void *)(*u)[inf_i] + 8L * (((inf_j) - (0L))), [3] = (void *)(*u)[inf_i - bx] + 8L * (((inf_j) - (0L))), [4] = (void *)(*u)[sup_i] + 8L * (((inf_j) - (0L))), [5] = (void *)(*u)[inf_i] + 8L * (((inf_j - by) - (0L))), [6] = (void *)(*u)[inf_i] + 8L * (((sup_j) - (0L)))};
                unsigned long int gomp_task_flags_1 = 0;
                gomp_task_flags_1 |= GOMP_TASK_DEPEND;
                unsigned int _gomp_task_instance_id_1 = 0;
                GOMP_task((void (*)(void *))_ol_main_1, &ol_data_1, (void (*)(void *, void *))0, 40, 8, 1, gomp_task_flags_1, gomp_task_deps_1, 0, 2U, _gomp_task_instance_id_1, GOMP_DYNAMIC_TDG);
              }
          }
      }
  }
  ;
}
struct gomp_ol_args_3_t;
extern _Bool GOMP_single_start(void);
struct  gomp_ol_args_3_t
{
  double *runtime;
  int *num_iter;
  int *np;
  double ***u;
  algoparam_t *param;
  unsigned int *iter;
};
double wtime();
extern void GOMP_taskwait(void);
extern void GOMP_barrier(void);
static void _ol_main_3(struct gomp_ol_args_3_t *ol_data_3)
{
  double *const runtime = &(*(*ol_data_3).runtime);
  int *const num_iter = &(*(*ol_data_3).num_iter);
  int *const np = &(*(*ol_data_3).np);
  double ***const u = &(*(*ol_data_3).u);
  algoparam_t *const param = &(*(*ol_data_3).param);
  unsigned int *const iter = &(*(*ol_data_3).iter);
  {
    if (GOMP_single_start())
      {
        {
          (*runtime) = wtime();
          for (int i = 0; i < (*num_iter); i++)
            {
              int nbx;
              int nby;
              int bx;
              int by;
              struct gomp_ol_args_2_t ol_data_2;
              double sum = 0.00000000000000000000000000000000000000000000000000000e+00;
              int sizex = (*np);
              int sizey = (*np);
              const long int mcc_vla_9 = sizey;
              (*u) = (double (*)[mcc_vla_9])(*param).u;
              nbx = 64;
              nby = 64;
              bx = sizex / nbx;
              by = sizey / nby;
              ol_data_2.nbx = nbx;
              ol_data_2.nby = nby;
              ol_data_2.bx = bx;
              ol_data_2.sizex = sizex;
              ol_data_2.by = by;
              ol_data_2.sizey = sizey;
              ol_data_2.iter = (unsigned int *) iter;
              ol_data_2.param = (algoparam_t *) param;
              ol_data_2.np = (int *) np;
              ol_data_2.u = (double ***) u;
              GOMP_exec_tdg((void (*)(void *))_ol_main_2, &ol_data_2);
              GOMP_taskwait();
            }
          GOMP_taskwait();
          (*runtime) = wtime() - (*runtime);
          printf("without parallel, we spent %.4f us\n", (*runtime));
        }
      }
    GOMP_barrier();
  }
  ;
}
extern void exit(int __status) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__noreturn__));
extern FILE *fopen(const char *__restrict __filename, const char *__restrict __modes) __attribute__((__warn_unused_result__));
extern size_t strlen(const char *__s) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__pure__)) __attribute__((__nonnull__(1)));
int read_input(FILE *infile, algoparam_t *param);
extern void __assert_fail(const char *__assertion, const char *__file, unsigned int __line, const char *__function) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__noreturn__));
int initialize(algoparam_t *param);
extern void *malloc(size_t __size) __attribute__((__nothrow__)) __attribute__((__leaf__)) __attribute__((__malloc__)) __attribute__((__warn_unused_result__));
extern void GOMP_parallel_start(void (*)(void *), void *, unsigned int);
extern void GOMP_parallel_end(void);
int finalize(algoparam_t *param);
int main(int argc, char **argv)
{
  FILE *infile;
  FILE *resfile;
  algoparam_t param;
  int np;
  double totalTime;
  struct gomp_ol_args_3_t ol_data_3;
  double runtime;
  static const char __MERCURIUM_PRETTY_FUNCTION__[24L] = "int main(int, char *[])";
  unsigned int iter = 0;
  if (argc < 3)
    {
      printf("num_iter as last argument needed\n");
      return 1;
    }
  int num_iter = atoi(argv[argc - 1]);
  if (num_iter < 0)
    {
      printf("num_iter must be positif\n");
      exit( -1);
    }
  if (!(infile = fopen(argv[1], "r")))
    {
      fprintf(stderr, "\nError: Cannot open \"%s\" for reading.\n\n", argv[1]);
      usage(argv[0]);
      return 1;
    }
  unsigned int size = strlen(argv[0]) + 4 + 1;
  char resfilename[size];
  resfilename[0] = '\000';
  strcat(resfilename, argv[0]);
  strcat(resfilename, ".ppm");
  if (!(resfile = fopen(resfilename, "w")))
    {
      fprintf(stderr, "\nError: Cannot open \"%s\" for writing.\n\n", resfilename);
      usage(argv[0]);
      return 1;
    }
  if (!read_input(infile, &param))
    {
      fprintf(stderr, "\nError: Error parsing input file.\n\n");
      usage(argv[0]);
      return 1;
    }
  ((void)sizeof(int),  ({
    if (param.algorithm == 1 && "Only Gauss-seidel is currently implemented\n")
      {
        ;
      }
    else
      {
        __assert_fail("(param.algorithm == 1) && \"Only Gauss-seidel is currently implemented\\n\"", "heat.c", 138, __MERCURIUM_PRETTY_FUNCTION__);
      }
  }) );
  if (!initialize(&param))
    {
      fprintf(stderr, "Error in Solver initialization.\n\n");
      usage(argv[0]);
      return 1;
    }
  np = param.resolution + 2;
  totalTime = 0;
  double *u_tmp = (double *)malloc(sizeof(double) * np * np);
  memcpy(u_tmp, param.u, sizeof(double) * np * np);
  ol_data_3.runtime = &runtime;
  ol_data_3.num_iter = &num_iter;
  ol_data_3.np = &np;
  ol_data_3.u = &u;
  ol_data_3.param = &param;
  ol_data_3.iter = &iter;
  GOMP_parallel_start((void (*)(void *))_ol_main_3, &ol_data_3, 0);
  _ol_main_3(&ol_data_3);
  GOMP_parallel_end();
  finalize(&param);
  return 0;
}
