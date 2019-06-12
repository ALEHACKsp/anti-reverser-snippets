# VMProtect/Themida virtualization guide

## Рандомизация секций кода

    function GetRandomSectionName()  
    local res = ""  
    for i = 1, 8 do  
    res = res .. string.char(32 + math.random(string.byte("z") - 32))  
    end  
    return res  
    end  
      
    function OnAfterSaveFile()  
    local file = vmprotect.core():outputArchitecture()  
    for i = 1, file:segments():count() do  
    segment = file:segments():item(i)  
    name = GetRandomSectionName()  
    print(string.format("Section \"%s\" is renamed to \"%s\"", segment:name(), name))  
    segment:setName(name)  
    end  
    end

## Пример использования маркеров

    extern "C" __declspec(dllexport)  
    void __cdecl SetSerialNumber(PCHAR PO)  
    {  
    VMProtectBeginUltra("SetSerialNumber Marker");  
    ValidSerialNumber = PO;  
    VMProtectEnd();  
    }

## Хранение результата проверки регистрации

  
Как правило программисты, уделившие много времени на саму процедуру регистрации совершенно забывают о защите самого результата регистрации программы:

    var IsRegistered: Boolean;  
    ...  
    procedure TForm1.Button1Click(Sender: TObject);  
    begin  
    ...  
    if not IsRegistered then  
    IsRegistered:=CheckRegistration(RegNumber);  
    if not IsRegistered then  
    exit;  
    ...  
    end;
В данном случае перед проверкой проверяется глобальная переменная, хранящая результат проверки, которая может использоваться в различных частях программы.  
Найти эту глобальную переменную не составит большого труда (просто просмотрев 2 сегмента данных на изменения ДО и ПОСЛЕ регистрации) - по такому принципу например работает всем известная программа ArtMoney. Рекомендуется все результаты проверок, отвечающих за регистрацию программы, хранить не в статической памяти, а в динамической. В случае хранения глобальных переменных в динамической памяти сканирование секций данных не предмет изменения ячеек памяти ДО и ПОСЛЕ регистрации ничего не даст крякеру.  
Простейший пример хранения результата в динамически выделяемой памяти:

    type PBoolean = ^Boolean;  
      
    var IsRegistered: PBoolean;  
    ...  
    procedure TForm1.Button1Click(Sender: TObject);  
    begin  
    ...  
    if not IsRegistered^ then  
    IsRegistered^:=CheckRegistration(RegNumber);  
    if not IsRegistered^ then  
    exit;  
    ...  
    end;  
    ...  
    initialization  
    New(IsRegistered);  

## Проверка регистрационных ключей

  
  
Очень часто программисты допускают грубейшие ошибки при реализации самой проверки правильности регистрационного ключа:  

    var ValidRegNumber: String;  
    ...  
    function CheckRegistration(const RegNumber: String): Boolean;  
    begin  
    if RegNumber=ValidRegNumber then  
    Result:=True  
    else  
    Result:=False;  
    end;

Взломщики не составит труда в процессе трассировки этого участка кода получить значение валидного ключа (просто подсмотрев значение параметров в функции сравнения строк). Поэтому рекомендуется для сравнения использовать хеши ключей:

    var  
    HashOfValidRegNumber: Longint;  
      
    ...  
      
    // Пример использования обобщенного алгоритма хеширования Питера Вейнбергер (PJW)  
    function HashPJW(const Value: String): Longint;  
    var I:Integer;  
    G:Longint;  
    begin  
    Result:=0;  
    for I:=1 to Length(Value) do  
    begin  
    Result:=(Result shl 4)+Ord(Value[I]);  
    G:=Result and $F0000000;  
    if G<>0 then  
    Result:=(Result xor (G shr 24)) xor G;  
    end;  
    end;  
      
    function CheckRegistration(const RegNumber: String): Boolean;  
    begin  
    if HashPJW(RegNumber)=HashOfValidRegNumber then  
    Result:=True  
    else  
    Result:=False;  
    end;  
      
    ...  
      
    initialization  
    HashOfValidRegNumber:=HashPJW(ValidRegNumber);  
      
    end.  
Суть данного метода состоит в том, что данная хеш функция необратима и по результатам проверки хешей ключей невозможно определить какой должен быть правильный ключ. Взломщику придется потратить гораздо больше времени на нахождение правильного регистрационного ключа, исследуя гораздо больше участков вашей программы, а не только саму проверку правильности ключа.

## Вызов процедуры регистрации
Если вы реализовываете свою схему регистрации, то никогда не выделяйте проверку в отдельную функцию, которая делает только саму проверку правильности ввода ключа и в результате возвращает только флаг проверки (верен или нет введенный регистрационный код).  
Рекомендуется вставлять проверку в саму логику работы вашей программы, чтобы невозможно было отделить сам алгоритм проверки регистрационного кода от алгоритма работы вызывающей эту проверку процедуры.  
  
Как делают большинство программистов:

    function CheckRegistration(const RegNumber: String): Boolean;  
    begin  
    if RegNumber='123' then  
    Result:=True  
    else  
    Result:=False;  
    end;  
      
    procedure TForm1.Button1Click(Sender: TObject);  
    begin  
    ...  
    if not CheckRegistration(RegNumber) then  
    exit;  
    Application.CreateForm(TForm2, Form2);  
    Form2.ShowModal;  
    ...  
    end;

При таком подходе к регистрации вашей программы крякер не будет разбираться с вашем алгоритмом проверки регистрационного кода (какой бы сложный он не был), а просто изменит код в самом начале CheckRegistration, который всегда будет возвращать True.

    function CheckRegistration(const RegNumber: String): Boolean;  
    begin  
    Result:=True;  
    exit;  
    ...  
    end;

Рекомендуется "примешивать" логику работы программы в саму проверку регистрационного кода (показан простейший пример, конечная реализация зависит только от фантазии самого разработчика):

    function CheckRegistration(const RegNumber: String): Boolean;  
    begin  
    if RegNumber='123' then  
    begin  
    Application.CreateForm(TForm2, Form2);  
    Result:=True  
    end  
    else  
    Result:=False;  
    end;  
      
    procedure TForm1.Button1Click(Sender: TObject);  
    begin  
    ...  
    Form2:=nil;  
    if not CheckRegistration(RegNumber) then  
    exit;  
    Form2.ShowModal;  
    ...  
    end;
После реализации подобной схемы регистрации программы крякеру нужно будет досканально разобрать работу CheckRegistration чтобы полностью обойти проверку регистрационного кода. Также рекомендуется завиртуализировать (обработать с помощью VMProtect в режиме "Виртуализация" или "Ультра") обе процедуры CheckRegistration и TForm1.Button1Click.
