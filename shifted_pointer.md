    #include <stdio.h>

    // 64KiB, but it's OK
    unsigned char secret_array[0x10000];

    void check_lic_key()
    {
      // pretend, lic_check has failed
      secret_array[0x6123]=1; // 1 mean failed
      // printf ("check failed\n");
      // exit(0); a cracker may patch here

      // or put there another value if check is succeeded
      // secret_array[0x6123]=0;
    };

    unsigned char get_byte_at_0x6000(unsigned char *a)
    {
      return *(a+0x6000);
    };

    void check_again()
    {
      if (get_byte_at_0x6000(secret_array+0x123)==1)
      {
        // do something mean (add watermark maybe) or report error:
        printf ("check failed\n");
      }
      else
      {
        // proceed further
      };
    };

    int main()
    {
      // at start:
      check_lic_key();

      // do something

      // ... and while in some very critical part:
      check_again();
    };
