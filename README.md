# VMProtect/Themida virtualization guide

## code sections

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

