# Simulation model of the processor using C++

3-address addressing <br/>
24-bit registers <br/>
Setting values, addition, division with a remainder <br/>

How values that go beyond the bitness are processed? <br/>
Since the processor is 24-bit, the maximum decimal number that can be set <br/>
is 8,388,607, the minimum is -8,388,608. If the number is greater than the maximum, <br/>
then the numbers "go in a circle" and it becomes close to the minimum. <br/>
For example: 8 388 607 + 1 = -8 388 608. The same and vice versa. <br/>

-----------------------------------------------------------------------------

# Імітаційна модель процесора на C++

3-адресна адресність <br/>
24-бітний процесор <br/>
Задання значень, додавання, ділення з остачею <br/>

Як обробляються числа, що виходять за межі бітності? <br/>
Оскільки процесор 24-бітний, то максимальне дестякове число, яке може бути <br/>
задане - це 8 388 607, мінімальне - -8 388 608. Якщо число більше за максимальне, <br/>
числа йдуть по колу і воно стає близьким до мінімального. <br/>
Наприклад: 8 388 607 + 1 = -8 388 608. Те саме і навпаки. <br/>
