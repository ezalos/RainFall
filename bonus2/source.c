

undefined4 main(int ac, char **av)
{
    undefined4 uVar1;
    char *pcVar2;
    int32_t iVar3;
    undefined4 *puVar4;
    undefined4 *puVar5;
    uint8_t uVar6;
    char *arg_8h;
    char *pcStack172;
    undefined4 uStack168;
    undefined4 auStack96 [19];
    char *pcStack20;
    int32_t var_ch;

    uVar6 = 0;
    if (ac == 0x3)
	{
        iVar3 = 0x13;
        puVar4 = auStack96;
        while (iVar3 != 0) {
            iVar3 = iVar3 + -1;
            *puVar4 = 0;
            puVar4 = puVar4 + 1;
        }
        pcStack172 = av[1];
        uStack168 = 0x28;
        sym.imp.strncpy();
        pcStack172 = av[2];
        uStack168 = 0x20;
        sym.imp.strncpy();
        arg_8h = "LANG";
        pcVar2 = (char *)sym.imp.getenv();
        pcStack20 = pcVar2;
        if (pcVar2 != (char *)0x0) {
            uStack168 = 2;
            pcStack172 = (char *)0x804873d;
            iVar3 = sym.imp.memcmp();
            if (iVar3 == 0) {
                _obj.language = 1;
                arg_8h = pcVar2;
            } else {
                uStack168 = 2;
                pcStack172 = (char *)0x8048740;
                arg_8h = pcStack20;
                iVar3 = sym.imp.memcmp();
                if (iVar3 == 0) {
                    _obj.language = 2;
                }
            }
        }
        iVar3 = 0x13;
        puVar4 = auStack96;
        puVar5 = (undefined4 *)&stack0xffffff50;
        while (iVar3 != 0) {
            iVar3 = iVar3 + -1;
            *puVar5 = *puVar4;
            puVar4 = puVar4 + (uint32_t)uVar6 * -2 + 1;
            puVar5 = puVar5 + (uint32_t)uVar6 * -2 + 1;
        }
        uVar1 = sym.greetuser((int32_t)arg_8h);
    } else {
        uVar1 = 1;
    }
    return uVar1;
}

void sym.greetuser(int32_t arg_8h)
{
    char *s1;
    uint32_t uStack72;
    undefined4 uStack68;
    uint32_t uStack64;
    undefined2 uStack60;
    char cStack58;

    if (language == 1)
	{
        s1 = "Hyvää päivää "._0_4_;
        uStack72 = "Hyvää päivää "._4_4_;
        uStack68 = "Hyvää päivää "._8_4_;
        uStack64 = "Hyvää päivää "._12_4_;
        uStack60 = "Hyvää päivää "._16_2_;
        cStack58 = "Hyvää päivää "[18];
    }
	else
	{
        if (language == 2)
		{
            s1 = "Goedemiddag! "._0_4_;
            uStack72 = "Goedemiddag! "._4_4_;
            uStack68 = "Goedemiddag! "._8_4_;
            uStack64 = uStack64 & 0xffff0000 | (uint32_t)"Goedemiddag! "._12_2_;
        }
		else
		{
            if (language == 0) {
                s1 = "Hello "._0_4_;
                uStack72._0_3_ = CONCAT12("Hello "[6], "Hello "._4_2_);
                uStack72 = uStack72 & 0xff000000 | (uint32_t)(unkuint3)uStack72;
            }
        }
    }
    sym.imp.strcat(&s1, &arg_8h);
    sym.imp.puts(&s1);
    return;
}
