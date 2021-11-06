# Integration Testing

 This code will create a task to run an integration tests on the function adcResToVoltage.
 Unit Under Test: adcResToVoltage() which determines whole and fractional part of voltage value corresponding to an ADC result

# Important Files

 Source file: main/user_main.c,
 Output file: main/lab3_q2_816005001.out,
 Binary file: build/i2c.bin

# Test file

 There is no explicit test file. The integration_test_task in main/user_main.c does the job of a test driver in this code.

# Pin Assignment

 N/A


# Hardware Required

 None

# Example Output  

```

I () main: Integration testing task
I () main: UUT: adcResToVoltage()
I () main: adcResToVoltage() determines both the whole and fractional part of voltage value corresponding to ADC result

I () main: Test case 1: ADC result: 0x0 [0]
I () main: Expected output > Whole: 0, Fraction: 0 / 16000
I () main: Output > Whole: 0, Fraction: 0 / 16000

I () main: Test case 2: ADC result: 0xa [10]
I () main: Expected output > Whole: 0, Fraction: 10 / 16000
I () main: output > Whole: 0, Fraction: 10 / 16000

I () main: Test case 3: ADC result: 0x5e1f [24095]
I () main: Expected output > Whole: 1, Fraction: 8095 / 16000
I () main: output > Whole: 1, Fraction: 8095 / 16000

I () main: Test case 4: ADC result: 0x6c1f [27679]
I () main: Expected output > Whole: 1, Fraction: 11679 / 16000
I () main: Output > Whole: 1, Fraction: 11679 / 16000

I () main: Test case 5: ADC result: 0xffff [65535]
I () main: Expected output > Whole: 4, Fraction: 1535 / 16000
I () main: Output > Whole: 4, Fraction: 1535 / 16000

```


