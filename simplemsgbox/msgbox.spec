x64:
        load "msgbox.o"
            make pic64 +optimize
            disassemable "out.txt"
            export
