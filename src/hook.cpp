// "proper" hotpatch example:
// https://github.com/i-saint/scribble/blob/master/Hotpatch.cpp

#include <cstdio>
#include <windows.h>

size_t slice_size = 0;
BYTE* old_func_buf = NULL;
// 
size_t CopyInstructions(void *dst_, const void *src_, size_t required)
{
    // �s���S�ɂ��A���Ή��� instruction ������ΓK�X�ǉ����ׂ�
    // �֐��̓� 5 byte �ȓ��Ŏ��s�������̂͑����� mov,sub,push ������Ȃ̂ł��ꂾ���ł������ɑΉ��͂ł���n�Y
    size_t ret = 0;
    const BYTE *src = (const BYTE*)src_;
    BYTE *dst = (BYTE*)dst_;

    for(; ret<required; ) {
        int size = 0; // instruction size
        bool can_memcpy = true;

        switch(src[ret]) {
        // push
        case 0x55: size=1; break;
        case 0x68:
        case 0x6A: size=5; break;
        case 0xFF:
            switch(src[ret+1]) {
            case 0x74: size=4; break;
            default:   size=3; break;
            }

        // mov
        case 0x8B:
            switch(src[ret+1]) {
            case 0x44: size=4; break;
            case 0x45: size=3; break;
            default:   size=2; break;
            }
            break;
        case 0xB8: size=5; break;

        // sub
        case 0x81: 
            switch(src[ret+1]) {
            case 0xEC: size=6; break;
            default:   size=2; break;
            }
            break;
        case 0x83:
            switch(src[ret+1]) {
            case 0xEC: size=3; break;
            default:   size=2; break;
            }
            break;

        // call & jmp
        case 0xE8:
        case 0xE9:
            {
                can_memcpy = false;
                int rva = *(int*)(src+1);
                dst[ret] = src[ret];
                *(DWORD*)(dst+ret+1) = (ptrdiff_t)(src+ret+rva)-(ptrdiff_t)(dst+ret);
                ret += 5;
            }
            break;

        default: size=1; break;
        }

        if(can_memcpy) {
            memcpy(dst+ret, src+ret, size);
        }
        ret += size;
    }

    return ret;
}

// target: �֐��|�C���^�B�Ώۊ֐����㏑�������̃R�[�h�͑ޔ����āA���̊֐��ւ̃|�C���^��Ԃ�
void* UglyHotpatch( void *target, const void *replacement )
{
    // ���R�[�h�̑ޔ��
    BYTE *preserved = (BYTE*)::VirtualAlloc(NULL, 64, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	old_func_buf = preserved;
	
    BYTE *f = (BYTE*)target;
    DWORD old;
    ::VirtualProtect(f, 32, PAGE_EXECUTE_READWRITE, &old);

    // ���̃R�[�h���R�s�[ & �Ō�ɃR�s�[�{�� jmp ����R�[�h��t�� (==����� call ����Ώ㏑���O�̓��������n�Y)
    size_t slice = CopyInstructions(preserved, f, 5);
	slice_size = slice;

    // �֐��̐擪�� hook �֐��ւ� jmp �ɏ���������
    f[0]=0xE9; // jmp
    *(DWORD*)(f+1) = (ptrdiff_t)replacement-(ptrdiff_t)f - 5;
    ::VirtualProtect(f, 32, old, &old);

    return preserved;
}

// �ޔ������A�Z���u���R�[�h�����̈ʒu�ɖ߂�����
void un_hook(void* target){
	if(old_func_buf != NULL){
		DWORD old;
    	::VirtualProtect(target, 32, PAGE_EXECUTE_READWRITE, &old);
		memcpy(target, old_func_buf, slice_size);
		::VirtualProtect(target, 32, old, &old);
	}
	old_func_buf = NULL;
}
