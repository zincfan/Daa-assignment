#include "intal.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static char* reversestring(char* string,int leng)
{
  char *revintal = malloc(sizeof(char) * (leng + 1));
  for(int i=0;i<leng;i++)
  {
    revintal[i]=string[leng-i-1];
  }
  revintal[leng]='\0';
  return revintal;
}

char *intal_add(const char *intal1, const char *intal2)
{
  long len1 = strlen(intal1);
  long len2 = strlen(intal2);
  int sum = 0, carry = 0, firstflag = 0, maxlen = len2, minlen = len1, sumstringlen = 0;
  if (len1 > len2)
  {
    firstflag = 1;
    maxlen = len1;
    minlen = len2;
  }
  char *stringsum;
  stringsum = malloc((maxlen + 2) * sizeof(char));
  char *revintal1 = reversestring(intal1, len1);
  char *revintal2 = reversestring(intal2, len2);
  for (int i = 0; i < minlen; i++)
  {
    sum = (revintal1[i] - '0') + (revintal2[i] - '0') + carry;
    carry = 0;
    if (sum > 9)
    {
      sum = sum % 10;
      carry = 1;
    }
    stringsum[i] = sum + '0';
    sumstringlen++;
  }
  stringsum[sumstringlen] = '\0';
  char *temp;
  if (firstflag)
    temp = revintal1;
  else
  {
    temp = revintal2;
  }
  for (int i = sumstringlen; i < maxlen; i++)
  {
    sum = temp[i] - '0' + carry;
    carry = 0;
    if (sum > 9)
    {
      sum = sum % 10;
      carry = 1;
    }
    stringsum[i] = sum + '0';
    sumstringlen++;
  }
  if (carry != 0)
    stringsum[sumstringlen++] = carry + '0';
  stringsum[sumstringlen] = '\0';
  char *res = reversestring(stringsum, sumstringlen);
  return res;
}

int intal_compare(const char *intal1, const char *intal2)
{
    long len1=strlen(intal1);
    long len2=strlen(intal2);
    if(len1>len2)
      return 1;
    else if(len2>len1)
      return -1;
    else
    {
      for(int i=0;i<len1;i++)
      {
        if(intal1[i]-'0'>intal2[i]-'0')
          return 1;
        else if (intal1[i] - '0' < intal2[i] - '0')
          return -1;
      }
      return 0;
    }  
}

char *intal_diff(const char *intal1, const char *intal2)
{
  long len1 = strlen(intal1);
  long len2 = strlen(intal2);
  int sum = 0, carry = 0, firstflag = 0, maxlen = len2, minlen = len1, diffstringlen = 0;
  int diff_intal = intal_compare(intal1, intal2);
  if (diff_intal == 1)
  {
    firstflag = 1;
    maxlen = len1;
    minlen = len2;
  }
  if (diff_intal == 0)
  {
    char *string1 = malloc(sizeof(char) * 2);
    string1[0] = '0';
    string1[1] = '\0';
    return string1;
  }
  char *stringdiff;
  stringdiff = malloc((maxlen + 1) * sizeof(char));
  char *revintal1;
  char *revintal2;
  if (firstflag)
  {
    revintal1 = reversestring(intal1, len1);
    revintal2 = reversestring(intal2, len2);
  }
  else
  {
    revintal2 = reversestring(intal1, len1);
    revintal1 = reversestring(intal2, len2);
  }
  int rem = 0;
  for (int i = 0; i < minlen; i++)
  {
    int firstnum = (revintal1[i] - '0') - rem;
    if (firstnum < 0)
      firstnum = 9;
    int diff = firstnum - (revintal2[i] - '0');
    rem = 0;
    if (diff < 0)
    {
      diff = 10 + firstnum - (revintal2[i] - '0');
      rem = 1;
    }
    stringdiff[i] = diff + '0';
    diffstringlen++;
  }
  char *temp = revintal1;
  for (int i = diffstringlen; i < maxlen; i++)
  {
    int diff = (temp[i] - '0') - rem;
    if (diff < 0)
    {
      diff = 10 + (temp[i] - '0') - rem;
      rem = 1;
    }
    stringdiff[i] = diff + '0';
    diffstringlen++;
  }
  for (int i = diffstringlen - 1; i > 0 && (stringdiff[i] == '0'); i--)
  {
    diffstringlen--;
  }
  stringdiff[diffstringlen] = '\0';
  char *res = reversestring(stringdiff, diffstringlen);
  return res;
}

char *intal_multiply(const char *intal1, const char *intal2)
{
  long len1 = strlen(intal1);
  long len2 = strlen(intal2);
  int firstflag = 0, maxlen = len2, minlen = len1, sumstringlen = 0;
  long long int sum = 0, carry = 0;
  char *revintal1 = reversestring(intal1, len1);
  char *revintal2 = reversestring(intal2, len2);
  int diff_intal = intal_compare(intal1, intal2);
  char *grate = revintal2;
  char *small = revintal1;
  if (diff_intal == 1)
  {
    firstflag = 1;
    maxlen = len1;
    minlen = len2;
    grate = revintal1;
    small = revintal2;
  }
  char *stringsum = malloc((1000) * sizeof(char));
  char *arr[minlen];
  for (int i = 0; i < minlen; i++)
  {
    arr[i] = malloc((maxlen + 2) * sizeof(char));
  }
  for (int i = 0; i < minlen; i++)
  {
    carry = 0;
    int j = 0;
    for (j = 0; j < maxlen; j++)
    {
      int mul = (small[i] - '0') * (grate[j] - '0') + carry;
      carry = 0;
      if (mul > 9)
      {
        carry = mul / 10;
        mul = mul % 10;
      }
      arr[i][j] = mul + '0';
    }
    arr[i][j++] = carry + '0';
    arr[i][j] = '\0';
  }
  carry = 0;
  for (int i = 0; i < minlen + maxlen; i++)
  {
    int startlevel = 0, startnumi, levels = minlen;
    if (i < maxlen + 1)
    {
      startlevel = 0;
      startnumi = i;
    }
    else
    {
      startlevel = i - (maxlen);
      startnumi = maxlen;
    }
    sum = 0;
    for (int j = startnumi; j >= 0 && startlevel < levels; j--)
    {
      sum = sum + arr[startlevel][j] - '0';
      startlevel++;
    }
    sum = sum + carry;
    carry = 0;
    if (sum > 9)
    {
      carry = sum / 10;
      sum = sum % 10;
    }
    stringsum[sumstringlen++] = sum + '0';
  }
  if (stringsum[sumstringlen - 1] == '0')
    sumstringlen--;
  stringsum[sumstringlen] = '\0';
  char *res = reversestring(stringsum, sumstringlen);
  return res;
}


char *intal_pow(const char *intal1, unsigned int n)
{
  if (n == 0)
  {
    char *res = malloc(sizeof(char) * 2);
    res[0] = '1';
    res[1] = '\0';
    return res;
  }
  if (strcmp(intal1, "0") == 0)
    return "1\0";
  char *halfresult = intal_pow(intal1, n / 2); //time problem here

  if (n % 2 == 0)
  {
    return intal_multiply(halfresult, halfresult);
  }
  else
  {
    char *res = intal_multiply(halfresult, halfresult);
    char *res_final = intal_multiply(res, intal1);
    return res_final;
  }
}

char *intal_gcd(const char *intal1, const char *intal2)
{
  int equality=intal_compare(intal1,intal2);
  if(equality == 0)
    return intal1;
  if(equality>0)
    return intal_gcd(intal_diff(intal1,intal2),intal2);
  else
  {
    return intal_gcd(intal1,intal_diff(intal2,intal1));
  }
  
}

char *intal_fibonacci(unsigned int n)
{
  if(n==0)
    return "0\0";
  else if(n==1)
    return "1\0";
  char *a=malloc(sizeof(char)*1000);
  char *b=malloc(sizeof(char)*1000);
  char *c=malloc(sizeof(char)*1000);
  a[0]='0';a[1]='\0';
  b[0]='1';b[1]='\0';
  int i=0;
  for(i=1;i<=n;i++)
  {
    c=intal_add(a,b);
    b=a;
    a=c;
  }
  return c;
}

char *intal_factorial(unsigned int n)
{
  if (n == 0)
    return "1\0";
  char *res = malloc(sizeof(char) * 234); //hehe boi
  res[0] = 1 + '0';
  res[1] = '\0';
  long int c = n;
  for (int i = 1; i <= n; i++)
  {
    int leng = snprintf(NULL, 0, "%d", i);
    char *mul = malloc(leng + 1);
    snprintf(mul, leng + 1, "%d", i);
    res = intal_multiply(res, mul);
  }
  return res;
}

char *intal_mod(const char *intal1, const char *intal2)
{
  int cmp = intal_compare(intal1, intal2);
  if (cmp == -1)
  {
    char *result = malloc((strlen(intal1) + 1) * sizeof(char));
    strcpy(result, intal1);
    return result;
  }
  else if (cmp == 0)
  {
    char *result = malloc(2 * sizeof(char));
    strcpy(result, "0");
    return result;
  }
  int p = strlen(intal2);
  int stop = strlen(intal1);
  char *current = malloc((strlen(intal2) + 2) * sizeof(char));
  for (int i = 0; i < p; ++i)
    current[i] = intal1[i];
  current[p] = '\0';
  do
  {
    if (intal_compare(current, intal2) == -1 && p < stop)
    {
      int len = strlen(current);
      if (strcmp(current, "0") == 0)
        len = 0;
      current[len] = intal1[p];
      current[len + 1] = '\0';
      ++p;
    }
    if (intal_compare(current, intal2) != -1)
    {
      char *result = intal_diff(current, intal2);
      while (intal_compare(result, intal2) > -1)
      {
        char *tmp = result;
        result = intal_diff(result, intal2);
        free(tmp);
      }
      strcpy(current, result);
      free(result);
    }
  } while (p < stop);
  current = realloc(current, (strlen(current) + 1) * sizeof(char));
  current[strlen(current) + 1] = '\0';
  return current;
}

int intal_max(char **arr, int n)
{
  char *max=malloc(sizeof(char)*2);
  max[0]=0+'0';max[1]='\0';
  int maxI=0;
  for(int i=0;i<n;i++)
  {
    int res=intal_compare(max,arr[i]);
    if(res<0)
    {
      max=arr[i];
      maxI=i;
    }
  }
  return maxI;
}

int intal_min(char **arr, int n)
{
  char *min = malloc(sizeof(char) * 1001);
  min = "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

  int minI = 0;
  for (int i = 0; i < n; i++)
  {
    int res = intal_compare(min, arr[i]);
    if (res > 0)
    {
      min = arr[i];
      minI = i;
    }
  }
  return minI;
}

int intal_search(char **arr, int n, const char *key)
{
  char *find = key;
  int findI = 0;
  for (int i = 0; i < n; i++)
  {
    int res = intal_compare(find, arr[i]);
    if (res == 0)
    {
      return i;
    }
  }
  return -1;
}

static int custom_waterloop_binsearch(int n, char *arr[n], const char *key, int start, int end)
{
  if (start >= 0 && end < n && start < end)
  {
    int mid = (start + end) / 2;
    int com = intal_compare(arr[mid], key);
    if (com == 0)
    {
      return mid;
    }
    else if (com > 0)
    {
      return custom_waterloop_binsearch(n, arr, key, start, mid - 1);
    }
    else
    {
      return custom_waterloop_binsearch(n, arr, key, mid + 1, end);
    }
  }
  else
  {
    return -1;
  }
}

static int custom_binsearch(int n, char *arr[n], const char *key, int start, int end)
{
  int res = custom_waterloop_binsearch(n, arr, key, start, end);
  int i = res - 1;
  for (i; i >= 0; i--)
  {
    if (intal_compare(arr[i], key) == 0)
      res--;
    else
      break;
  }
  return res;
}

int intal_binsearch(char **arr, int n, const char *key)
{
  int start = 0, end = n - 1, mid;
  int res = custom_binsearch(n, arr, key, start, end);
  return res;
}

void intal_merge(int n, char *arr[n], int start1, int end1, int start2, int end2)
{
  int i = start1, j = start2;
  char *resarr[end2 - start1 + 2];
  int resc = 0;
  while (i <= end1 && j <= end2)
  {
    if (intal_compare(arr[i], arr[j]) > 0)
    {
      resarr[resc++] = arr[j];
      j++;
    }
    else
    {
      resarr[resc++] = arr[i];
      i++;
    }
  }
  if (i != end1)
  {
    while (i <= end1)
    {
      resarr[resc++] = arr[i++];
    }
  }
  if (j != end2)
  {
    while (j <= end2)
    {
      resarr[resc++] = arr[j++];
    }
  }
  int resarrrc = 0;
  for (int i = start1; i <= end2 && resarrrc < resc; i++)
  {
    arr[i] = resarr[resarrrc++];
  }
}

void intal_mergesort(int n, char *arr[n], int start, int end)
{
  if (start < end)
  {
    int mid = (start + end) / 2;
    intal_mergesort(n, arr, start, mid);
    intal_mergesort(n, arr, mid + 1, end);
    intal_merge(n, arr, start, mid, mid + 1, end);
  }
}

void intal_sort(char **arr, int n)
{
  intal_mergesort(n, arr, 0, n - 1);
}

char *intal_bincoeff(unsigned int n, unsigned int k)
{
  char **C = malloc(sizeof(char *) * (k + 1));
  for (int i = 0; i < k + 2; i++)
  {
    C[i] = malloc(sizeof(char) * 1000000000000000);
    C[i] = "0\0";
  }

  C[k + 1] = "\0";
  C[0] = "1";
  for (int i = 1; i <= n; i++)
  {
    int mini = i;
    if (i > k)
      mini = k;
    for (int j = mini; j > 0; j--)
    {
      C[j] = intal_add(C[j], C[j - 1]);
    }
  }
  return C[k];
}

static char *intal_div2(const char *intal1)
{
  int i = 0, carry = 0;
  char *res = malloc(sizeof(char) * (strlen(intal1) + 1));
  int resc = 0, flag = 1;
  while (intal1[i] != '\0')
  {
    int num = intal1[i] - '0';
    num = num + carry * 10;

    carry = 0;
    int cal = num / 2;
    if (num % 2 != 0)
      carry = 1;
    res[resc++] = cal + '0';
    i++;
  }
  res[resc] = '\0';
  char *res2 = malloc(sizeof(char) * (strlen(intal1) + 1));
  strncpy(res2, res + 1, resc - 1);
  res2[resc - 1] = '\0';
  free(res);
  return res2;
}

char *coin_row_problem(char **arr, int n)
{
  char **f = malloc((n + 1) * sizeof(char *));
  f[0] = malloc(2 * sizeof(char));
  f[0][0] = '\0';
  f[0][1] = '\0';

  for (int i = 0; i < n; i++)
  {
    f[i + 1] = malloc((strlen(arr[i]) + 1) * sizeof(char));
    strcpy(f[i + 1], arr[i]);
  }

  for (int i = 2; i < n + 1; i++)
  {
    char *val = intal_add(arr[i - 1], f[i - 2]);
    if (intal_compare(val, f[i - 1]) > 0)
    {
      char *tmp = f[i];
      f[i] = val;
      free(tmp);
    }
    else
    {
      free(f[i]);
      f[i] = malloc((strlen(f[i - 1]) + 1) * sizeof(char));
      strcpy(f[i], f[i - 1]);
      free(val);
    }
  }

  char *result = malloc((strlen(f[n]) + 1) * sizeof(char));
  strcpy(result, f[n]);

  for (int i = 0; i < n + 1; i++)
  {
    free(f[i]);
  }
  free(f);
  return result;
}
