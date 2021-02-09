
ctarget:     file format elf64-x86-64


Disassembly of section .init:

0000000000400c48 <_init>:
  400c48:	48 83 ec 08          	sub    $0x8,%rsp
  400c4c:	48 8b 05 a5 33 20 00 	mov    0x2033a5(%rip),%rax        # 603ff8 <__gmon_start__>
  400c53:	48 85 c0             	test   %rax,%rax
  400c56:	74 05                	je     400c5d <_init+0x15>
  400c58:	e8 43 02 00 00       	callq  400ea0 <__gmon_start__@plt>
  400c5d:	48 83 c4 08          	add    $0x8,%rsp
  400c61:	c3                   	retq   

Disassembly of section .plt:

0000000000400c70 <.plt>:
  400c70:	ff 35 92 33 20 00    	pushq  0x203392(%rip)        # 604008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400c76:	ff 25 94 33 20 00    	jmpq   *0x203394(%rip)        # 604010 <_GLOBAL_OFFSET_TABLE_+0x10>
  400c7c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400c80 <strcasecmp@plt>:
  400c80:	ff 25 92 33 20 00    	jmpq   *0x203392(%rip)        # 604018 <strcasecmp@GLIBC_2.2.5>
  400c86:	68 00 00 00 00       	pushq  $0x0
  400c8b:	e9 e0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400c90 <__errno_location@plt>:
  400c90:	ff 25 8a 33 20 00    	jmpq   *0x20338a(%rip)        # 604020 <__errno_location@GLIBC_2.2.5>
  400c96:	68 01 00 00 00       	pushq  $0x1
  400c9b:	e9 d0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400ca0 <srandom@plt>:
  400ca0:	ff 25 82 33 20 00    	jmpq   *0x203382(%rip)        # 604028 <srandom@GLIBC_2.2.5>
  400ca6:	68 02 00 00 00       	pushq  $0x2
  400cab:	e9 c0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cb0 <strncmp@plt>:
  400cb0:	ff 25 7a 33 20 00    	jmpq   *0x20337a(%rip)        # 604030 <strncmp@GLIBC_2.2.5>
  400cb6:	68 03 00 00 00       	pushq  $0x3
  400cbb:	e9 b0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cc0 <strcpy@plt>:
  400cc0:	ff 25 72 33 20 00    	jmpq   *0x203372(%rip)        # 604038 <strcpy@GLIBC_2.2.5>
  400cc6:	68 04 00 00 00       	pushq  $0x4
  400ccb:	e9 a0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cd0 <puts@plt>:
  400cd0:	ff 25 6a 33 20 00    	jmpq   *0x20336a(%rip)        # 604040 <puts@GLIBC_2.2.5>
  400cd6:	68 05 00 00 00       	pushq  $0x5
  400cdb:	e9 90 ff ff ff       	jmpq   400c70 <.plt>

0000000000400ce0 <write@plt>:
  400ce0:	ff 25 62 33 20 00    	jmpq   *0x203362(%rip)        # 604048 <write@GLIBC_2.2.5>
  400ce6:	68 06 00 00 00       	pushq  $0x6
  400ceb:	e9 80 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cf0 <__stack_chk_fail@plt>:
  400cf0:	ff 25 5a 33 20 00    	jmpq   *0x20335a(%rip)        # 604050 <__stack_chk_fail@GLIBC_2.4>
  400cf6:	68 07 00 00 00       	pushq  $0x7
  400cfb:	e9 70 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d00 <mmap@plt>:
  400d00:	ff 25 52 33 20 00    	jmpq   *0x203352(%rip)        # 604058 <mmap@GLIBC_2.2.5>
  400d06:	68 08 00 00 00       	pushq  $0x8
  400d0b:	e9 60 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d10 <memset@plt>:
  400d10:	ff 25 4a 33 20 00    	jmpq   *0x20334a(%rip)        # 604060 <memset@GLIBC_2.2.5>
  400d16:	68 09 00 00 00       	pushq  $0x9
  400d1b:	e9 50 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d20 <alarm@plt>:
  400d20:	ff 25 42 33 20 00    	jmpq   *0x203342(%rip)        # 604068 <alarm@GLIBC_2.2.5>
  400d26:	68 0a 00 00 00       	pushq  $0xa
  400d2b:	e9 40 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d30 <close@plt>:
  400d30:	ff 25 3a 33 20 00    	jmpq   *0x20333a(%rip)        # 604070 <close@GLIBC_2.2.5>
  400d36:	68 0b 00 00 00       	pushq  $0xb
  400d3b:	e9 30 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d40 <read@plt>:
  400d40:	ff 25 32 33 20 00    	jmpq   *0x203332(%rip)        # 604078 <read@GLIBC_2.2.5>
  400d46:	68 0c 00 00 00       	pushq  $0xc
  400d4b:	e9 20 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d50 <__libc_start_main@plt>:
  400d50:	ff 25 2a 33 20 00    	jmpq   *0x20332a(%rip)        # 604080 <__libc_start_main@GLIBC_2.2.5>
  400d56:	68 0d 00 00 00       	pushq  $0xd
  400d5b:	e9 10 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d60 <signal@plt>:
  400d60:	ff 25 22 33 20 00    	jmpq   *0x203322(%rip)        # 604088 <signal@GLIBC_2.2.5>
  400d66:	68 0e 00 00 00       	pushq  $0xe
  400d6b:	e9 00 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d70 <gethostbyname@plt>:
  400d70:	ff 25 1a 33 20 00    	jmpq   *0x20331a(%rip)        # 604090 <gethostbyname@GLIBC_2.2.5>
  400d76:	68 0f 00 00 00       	pushq  $0xf
  400d7b:	e9 f0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400d80 <__memmove_chk@plt>:
  400d80:	ff 25 12 33 20 00    	jmpq   *0x203312(%rip)        # 604098 <__memmove_chk@GLIBC_2.3.4>
  400d86:	68 10 00 00 00       	pushq  $0x10
  400d8b:	e9 e0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400d90 <strtol@plt>:
  400d90:	ff 25 0a 33 20 00    	jmpq   *0x20330a(%rip)        # 6040a0 <strtol@GLIBC_2.2.5>
  400d96:	68 11 00 00 00       	pushq  $0x11
  400d9b:	e9 d0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400da0 <memcpy@plt>:
  400da0:	ff 25 02 33 20 00    	jmpq   *0x203302(%rip)        # 6040a8 <memcpy@GLIBC_2.14>
  400da6:	68 12 00 00 00       	pushq  $0x12
  400dab:	e9 c0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400db0 <time@plt>:
  400db0:	ff 25 fa 32 20 00    	jmpq   *0x2032fa(%rip)        # 6040b0 <time@GLIBC_2.2.5>
  400db6:	68 13 00 00 00       	pushq  $0x13
  400dbb:	e9 b0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400dc0 <random@plt>:
  400dc0:	ff 25 f2 32 20 00    	jmpq   *0x2032f2(%rip)        # 6040b8 <random@GLIBC_2.2.5>
  400dc6:	68 14 00 00 00       	pushq  $0x14
  400dcb:	e9 a0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400dd0 <_IO_getc@plt>:
  400dd0:	ff 25 ea 32 20 00    	jmpq   *0x2032ea(%rip)        # 6040c0 <_IO_getc@GLIBC_2.2.5>
  400dd6:	68 15 00 00 00       	pushq  $0x15
  400ddb:	e9 90 fe ff ff       	jmpq   400c70 <.plt>

0000000000400de0 <__isoc99_sscanf@plt>:
  400de0:	ff 25 e2 32 20 00    	jmpq   *0x2032e2(%rip)        # 6040c8 <__isoc99_sscanf@GLIBC_2.7>
  400de6:	68 16 00 00 00       	pushq  $0x16
  400deb:	e9 80 fe ff ff       	jmpq   400c70 <.plt>

0000000000400df0 <munmap@plt>:
  400df0:	ff 25 da 32 20 00    	jmpq   *0x2032da(%rip)        # 6040d0 <munmap@GLIBC_2.2.5>
  400df6:	68 17 00 00 00       	pushq  $0x17
  400dfb:	e9 70 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e00 <__printf_chk@plt>:
  400e00:	ff 25 d2 32 20 00    	jmpq   *0x2032d2(%rip)        # 6040d8 <__printf_chk@GLIBC_2.3.4>
  400e06:	68 18 00 00 00       	pushq  $0x18
  400e0b:	e9 60 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e10 <fopen@plt>:
  400e10:	ff 25 ca 32 20 00    	jmpq   *0x2032ca(%rip)        # 6040e0 <fopen@GLIBC_2.2.5>
  400e16:	68 19 00 00 00       	pushq  $0x19
  400e1b:	e9 50 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e20 <getopt@plt>:
  400e20:	ff 25 c2 32 20 00    	jmpq   *0x2032c2(%rip)        # 6040e8 <getopt@GLIBC_2.2.5>
  400e26:	68 1a 00 00 00       	pushq  $0x1a
  400e2b:	e9 40 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e30 <strtoul@plt>:
  400e30:	ff 25 ba 32 20 00    	jmpq   *0x2032ba(%rip)        # 6040f0 <strtoul@GLIBC_2.2.5>
  400e36:	68 1b 00 00 00       	pushq  $0x1b
  400e3b:	e9 30 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e40 <gethostname@plt>:
  400e40:	ff 25 b2 32 20 00    	jmpq   *0x2032b2(%rip)        # 6040f8 <gethostname@GLIBC_2.2.5>
  400e46:	68 1c 00 00 00       	pushq  $0x1c
  400e4b:	e9 20 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e50 <exit@plt>:
  400e50:	ff 25 aa 32 20 00    	jmpq   *0x2032aa(%rip)        # 604100 <exit@GLIBC_2.2.5>
  400e56:	68 1d 00 00 00       	pushq  $0x1d
  400e5b:	e9 10 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e60 <connect@plt>:
  400e60:	ff 25 a2 32 20 00    	jmpq   *0x2032a2(%rip)        # 604108 <connect@GLIBC_2.2.5>
  400e66:	68 1e 00 00 00       	pushq  $0x1e
  400e6b:	e9 00 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e70 <__fprintf_chk@plt>:
  400e70:	ff 25 9a 32 20 00    	jmpq   *0x20329a(%rip)        # 604110 <__fprintf_chk@GLIBC_2.3.4>
  400e76:	68 1f 00 00 00       	pushq  $0x1f
  400e7b:	e9 f0 fd ff ff       	jmpq   400c70 <.plt>

0000000000400e80 <__sprintf_chk@plt>:
  400e80:	ff 25 92 32 20 00    	jmpq   *0x203292(%rip)        # 604118 <__sprintf_chk@GLIBC_2.3.4>
  400e86:	68 20 00 00 00       	pushq  $0x20
  400e8b:	e9 e0 fd ff ff       	jmpq   400c70 <.plt>

0000000000400e90 <socket@plt>:
  400e90:	ff 25 8a 32 20 00    	jmpq   *0x20328a(%rip)        # 604120 <socket@GLIBC_2.2.5>
  400e96:	68 21 00 00 00       	pushq  $0x21
  400e9b:	e9 d0 fd ff ff       	jmpq   400c70 <.plt>

Disassembly of section .plt.got:

0000000000400ea0 <__gmon_start__@plt>:
  400ea0:	ff 25 52 31 20 00    	jmpq   *0x203152(%rip)        # 603ff8 <__gmon_start__>
  400ea6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000400eb0 <_start>:
  400eb0:	31 ed                	xor    %ebp,%ebp
  400eb2:	49 89 d1             	mov    %rdx,%r9
  400eb5:	5e                   	pop    %rsi
  400eb6:	48 89 e2             	mov    %rsp,%rdx
  400eb9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  400ebd:	50                   	push   %rax
  400ebe:	54                   	push   %rsp
  400ebf:	49 c7 c0 e0 2d 40 00 	mov    $0x402de0,%r8
  400ec6:	48 c7 c1 70 2d 40 00 	mov    $0x402d70,%rcx
  400ecd:	48 c7 c7 b5 11 40 00 	mov    $0x4011b5,%rdi
  400ed4:	e8 77 fe ff ff       	callq  400d50 <__libc_start_main@plt>
  400ed9:	f4                   	hlt    
  400eda:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400ee0 <deregister_tm_clones>:
  400ee0:	b8 b7 44 60 00       	mov    $0x6044b7,%eax
  400ee5:	55                   	push   %rbp
  400ee6:	48 2d b0 44 60 00    	sub    $0x6044b0,%rax
  400eec:	48 83 f8 0e          	cmp    $0xe,%rax
  400ef0:	48 89 e5             	mov    %rsp,%rbp
  400ef3:	76 1b                	jbe    400f10 <deregister_tm_clones+0x30>
  400ef5:	b8 00 00 00 00       	mov    $0x0,%eax
  400efa:	48 85 c0             	test   %rax,%rax
  400efd:	74 11                	je     400f10 <deregister_tm_clones+0x30>
  400eff:	5d                   	pop    %rbp
  400f00:	bf b0 44 60 00       	mov    $0x6044b0,%edi
  400f05:	ff e0                	jmpq   *%rax
  400f07:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  400f0e:	00 00 
  400f10:	5d                   	pop    %rbp
  400f11:	c3                   	retq   
  400f12:	0f 1f 40 00          	nopl   0x0(%rax)
  400f16:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400f1d:	00 00 00 

0000000000400f20 <register_tm_clones>:
  400f20:	be b0 44 60 00       	mov    $0x6044b0,%esi
  400f25:	55                   	push   %rbp
  400f26:	48 81 ee b0 44 60 00 	sub    $0x6044b0,%rsi
  400f2d:	48 c1 fe 03          	sar    $0x3,%rsi
  400f31:	48 89 e5             	mov    %rsp,%rbp
  400f34:	48 89 f0             	mov    %rsi,%rax
  400f37:	48 c1 e8 3f          	shr    $0x3f,%rax
  400f3b:	48 01 c6             	add    %rax,%rsi
  400f3e:	48 d1 fe             	sar    %rsi
  400f41:	74 15                	je     400f58 <register_tm_clones+0x38>
  400f43:	b8 00 00 00 00       	mov    $0x0,%eax
  400f48:	48 85 c0             	test   %rax,%rax
  400f4b:	74 0b                	je     400f58 <register_tm_clones+0x38>
  400f4d:	5d                   	pop    %rbp
  400f4e:	bf b0 44 60 00       	mov    $0x6044b0,%edi
  400f53:	ff e0                	jmpq   *%rax
  400f55:	0f 1f 00             	nopl   (%rax)
  400f58:	5d                   	pop    %rbp
  400f59:	c3                   	retq   
  400f5a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400f60 <__do_global_dtors_aux>:
  400f60:	80 3d 81 35 20 00 00 	cmpb   $0x0,0x203581(%rip)        # 6044e8 <completed.7594>
  400f67:	75 11                	jne    400f7a <__do_global_dtors_aux+0x1a>
  400f69:	55                   	push   %rbp
  400f6a:	48 89 e5             	mov    %rsp,%rbp
  400f6d:	e8 6e ff ff ff       	callq  400ee0 <deregister_tm_clones>
  400f72:	5d                   	pop    %rbp
  400f73:	c6 05 6e 35 20 00 01 	movb   $0x1,0x20356e(%rip)        # 6044e8 <completed.7594>
  400f7a:	f3 c3                	repz retq 
  400f7c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400f80 <frame_dummy>:
  400f80:	bf 20 3e 60 00       	mov    $0x603e20,%edi
  400f85:	48 83 3f 00          	cmpq   $0x0,(%rdi)
  400f89:	75 05                	jne    400f90 <frame_dummy+0x10>
  400f8b:	eb 93                	jmp    400f20 <register_tm_clones>
  400f8d:	0f 1f 00             	nopl   (%rax)
  400f90:	b8 00 00 00 00       	mov    $0x0,%eax
  400f95:	48 85 c0             	test   %rax,%rax
  400f98:	74 f1                	je     400f8b <frame_dummy+0xb>
  400f9a:	55                   	push   %rbp
  400f9b:	48 89 e5             	mov    %rsp,%rbp
  400f9e:	ff d0                	callq  *%rax
  400fa0:	5d                   	pop    %rbp
  400fa1:	e9 7a ff ff ff       	jmpq   400f20 <register_tm_clones>

0000000000400fa6 <usage>:
  400fa6:	48 83 ec 08          	sub    $0x8,%rsp
  400faa:	48 89 fa             	mov    %rdi,%rdx
  400fad:	83 3d 74 35 20 00 00 	cmpl   $0x0,0x203574(%rip)        # 604528 <is_checker>
  400fb4:	74 3e                	je     400ff4 <usage+0x4e>
  400fb6:	be f8 2d 40 00       	mov    $0x402df8,%esi
  400fbb:	bf 01 00 00 00       	mov    $0x1,%edi
  400fc0:	b8 00 00 00 00       	mov    $0x0,%eax
  400fc5:	e8 36 fe ff ff       	callq  400e00 <__printf_chk@plt>
  400fca:	bf 30 2e 40 00       	mov    $0x402e30,%edi
  400fcf:	e8 fc fc ff ff       	callq  400cd0 <puts@plt>
  400fd4:	bf a8 2f 40 00       	mov    $0x402fa8,%edi
  400fd9:	e8 f2 fc ff ff       	callq  400cd0 <puts@plt>
  400fde:	bf 58 2e 40 00       	mov    $0x402e58,%edi
  400fe3:	e8 e8 fc ff ff       	callq  400cd0 <puts@plt>
  400fe8:	bf c2 2f 40 00       	mov    $0x402fc2,%edi
  400fed:	e8 de fc ff ff       	callq  400cd0 <puts@plt>
  400ff2:	eb 32                	jmp    401026 <usage+0x80>
  400ff4:	be de 2f 40 00       	mov    $0x402fde,%esi
  400ff9:	bf 01 00 00 00       	mov    $0x1,%edi
  400ffe:	b8 00 00 00 00       	mov    $0x0,%eax
  401003:	e8 f8 fd ff ff       	callq  400e00 <__printf_chk@plt>
  401008:	bf 80 2e 40 00       	mov    $0x402e80,%edi
  40100d:	e8 be fc ff ff       	callq  400cd0 <puts@plt>
  401012:	bf a8 2e 40 00       	mov    $0x402ea8,%edi
  401017:	e8 b4 fc ff ff       	callq  400cd0 <puts@plt>
  40101c:	bf fc 2f 40 00       	mov    $0x402ffc,%edi
  401021:	e8 aa fc ff ff       	callq  400cd0 <puts@plt>
  401026:	bf 00 00 00 00       	mov    $0x0,%edi
  40102b:	e8 20 fe ff ff       	callq  400e50 <exit@plt>

0000000000401030 <initialize_target>:
  401030:	55                   	push   %rbp
  401031:	53                   	push   %rbx
  401032:	48 81 ec 18 21 00 00 	sub    $0x2118,%rsp
  401039:	89 f5                	mov    %esi,%ebp
  40103b:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401042:	00 00 
  401044:	48 89 84 24 08 21 00 	mov    %rax,0x2108(%rsp)
  40104b:	00 
  40104c:	31 c0                	xor    %eax,%eax
  40104e:	89 3d c4 34 20 00    	mov    %edi,0x2034c4(%rip)        # 604518 <check_level>
  401054:	8b 3d 0e 31 20 00    	mov    0x20310e(%rip),%edi        # 604168 <target_id>
  40105a:	e8 f2 1c 00 00       	callq  402d51 <gencookie>
  40105f:	89 05 bf 34 20 00    	mov    %eax,0x2034bf(%rip)        # 604524 <cookie>
  401065:	89 c7                	mov    %eax,%edi
  401067:	e8 e5 1c 00 00       	callq  402d51 <gencookie>
  40106c:	89 05 ae 34 20 00    	mov    %eax,0x2034ae(%rip)        # 604520 <authkey>
  401072:	8b 05 f0 30 20 00    	mov    0x2030f0(%rip),%eax        # 604168 <target_id>
  401078:	8d 78 01             	lea    0x1(%rax),%edi
  40107b:	e8 20 fc ff ff       	callq  400ca0 <srandom@plt>
  401080:	e8 3b fd ff ff       	callq  400dc0 <random@plt>
  401085:	89 c7                	mov    %eax,%edi
  401087:	e8 03 03 00 00       	callq  40138f <scramble>
  40108c:	89 c3                	mov    %eax,%ebx
  40108e:	85 ed                	test   %ebp,%ebp
  401090:	74 18                	je     4010aa <initialize_target+0x7a>
  401092:	bf 00 00 00 00       	mov    $0x0,%edi
  401097:	e8 14 fd ff ff       	callq  400db0 <time@plt>
  40109c:	89 c7                	mov    %eax,%edi
  40109e:	e8 fd fb ff ff       	callq  400ca0 <srandom@plt>
  4010a3:	e8 18 fd ff ff       	callq  400dc0 <random@plt>
  4010a8:	eb 05                	jmp    4010af <initialize_target+0x7f>
  4010aa:	b8 00 00 00 00       	mov    $0x0,%eax
  4010af:	01 c3                	add    %eax,%ebx
  4010b1:	0f b7 db             	movzwl %bx,%ebx
  4010b4:	8d 04 dd 00 01 00 00 	lea    0x100(,%rbx,8),%eax
  4010bb:	89 c0                	mov    %eax,%eax
  4010bd:	48 89 05 dc 33 20 00 	mov    %rax,0x2033dc(%rip)        # 6044a0 <buf_offset>
  4010c4:	c6 05 7d 40 20 00 63 	movb   $0x63,0x20407d(%rip)        # 605148 <target_prefix>
  4010cb:	83 3d d6 33 20 00 00 	cmpl   $0x0,0x2033d6(%rip)        # 6044a8 <notify>
  4010d2:	0f 84 bb 00 00 00    	je     401193 <initialize_target+0x163>
  4010d8:	83 3d 49 34 20 00 00 	cmpl   $0x0,0x203449(%rip)        # 604528 <is_checker>
  4010df:	0f 85 ae 00 00 00    	jne    401193 <initialize_target+0x163>
  4010e5:	be 00 01 00 00       	mov    $0x100,%esi
  4010ea:	48 89 e7             	mov    %rsp,%rdi
  4010ed:	e8 4e fd ff ff       	callq  400e40 <gethostname@plt>
  4010f2:	85 c0                	test   %eax,%eax
  4010f4:	74 25                	je     40111b <initialize_target+0xeb>
  4010f6:	bf d8 2e 40 00       	mov    $0x402ed8,%edi
  4010fb:	e8 d0 fb ff ff       	callq  400cd0 <puts@plt>
  401100:	bf 08 00 00 00       	mov    $0x8,%edi
  401105:	e8 46 fd ff ff       	callq  400e50 <exit@plt>
  40110a:	48 89 e6             	mov    %rsp,%rsi
  40110d:	e8 6e fb ff ff       	callq  400c80 <strcasecmp@plt>
  401112:	85 c0                	test   %eax,%eax
  401114:	74 21                	je     401137 <initialize_target+0x107>
  401116:	83 c3 01             	add    $0x1,%ebx
  401119:	eb 05                	jmp    401120 <initialize_target+0xf0>
  40111b:	bb 00 00 00 00       	mov    $0x0,%ebx
  401120:	48 63 c3             	movslq %ebx,%rax
  401123:	48 8b 3c c5 80 41 60 	mov    0x604180(,%rax,8),%rdi
  40112a:	00 
  40112b:	48 85 ff             	test   %rdi,%rdi
  40112e:	75 da                	jne    40110a <initialize_target+0xda>
  401130:	b8 00 00 00 00       	mov    $0x0,%eax
  401135:	eb 05                	jmp    40113c <initialize_target+0x10c>
  401137:	b8 01 00 00 00       	mov    $0x1,%eax
  40113c:	85 c0                	test   %eax,%eax
  40113e:	75 1c                	jne    40115c <initialize_target+0x12c>
  401140:	48 89 e2             	mov    %rsp,%rdx
  401143:	be 10 2f 40 00       	mov    $0x402f10,%esi
  401148:	bf 01 00 00 00       	mov    $0x1,%edi
  40114d:	e8 ae fc ff ff       	callq  400e00 <__printf_chk@plt>
  401152:	bf 08 00 00 00       	mov    $0x8,%edi
  401157:	e8 f4 fc ff ff       	callq  400e50 <exit@plt>
  40115c:	48 8d bc 24 00 01 00 	lea    0x100(%rsp),%rdi
  401163:	00 
  401164:	e8 52 19 00 00       	callq  402abb <init_driver>
  401169:	85 c0                	test   %eax,%eax
  40116b:	79 26                	jns    401193 <initialize_target+0x163>
  40116d:	48 8d 94 24 00 01 00 	lea    0x100(%rsp),%rdx
  401174:	00 
  401175:	be 50 2f 40 00       	mov    $0x402f50,%esi
  40117a:	bf 01 00 00 00       	mov    $0x1,%edi
  40117f:	b8 00 00 00 00       	mov    $0x0,%eax
  401184:	e8 77 fc ff ff       	callq  400e00 <__printf_chk@plt>
  401189:	bf 08 00 00 00       	mov    $0x8,%edi
  40118e:	e8 bd fc ff ff       	callq  400e50 <exit@plt>
  401193:	48 8b 84 24 08 21 00 	mov    0x2108(%rsp),%rax
  40119a:	00 
  40119b:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4011a2:	00 00 
  4011a4:	74 05                	je     4011ab <initialize_target+0x17b>
  4011a6:	e8 45 fb ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  4011ab:	48 81 c4 18 21 00 00 	add    $0x2118,%rsp
  4011b2:	5b                   	pop    %rbx
  4011b3:	5d                   	pop    %rbp
  4011b4:	c3                   	retq   

00000000004011b5 <main>:
  4011b5:	41 56                	push   %r14
  4011b7:	41 55                	push   %r13
  4011b9:	41 54                	push   %r12
  4011bb:	55                   	push   %rbp
  4011bc:	53                   	push   %rbx
  4011bd:	41 89 fc             	mov    %edi,%r12d
  4011c0:	48 89 f3             	mov    %rsi,%rbx
  4011c3:	be f6 1d 40 00       	mov    $0x401df6,%esi
  4011c8:	bf 0b 00 00 00       	mov    $0xb,%edi
  4011cd:	e8 8e fb ff ff       	callq  400d60 <signal@plt>
  4011d2:	be a8 1d 40 00       	mov    $0x401da8,%esi
  4011d7:	bf 07 00 00 00       	mov    $0x7,%edi
  4011dc:	e8 7f fb ff ff       	callq  400d60 <signal@plt>
  4011e1:	be 44 1e 40 00       	mov    $0x401e44,%esi
  4011e6:	bf 04 00 00 00       	mov    $0x4,%edi
  4011eb:	e8 70 fb ff ff       	callq  400d60 <signal@plt>
  4011f0:	83 3d 31 33 20 00 00 	cmpl   $0x0,0x203331(%rip)        # 604528 <is_checker>
  4011f7:	74 20                	je     401219 <main+0x64>
  4011f9:	be 92 1e 40 00       	mov    $0x401e92,%esi
  4011fe:	bf 0e 00 00 00       	mov    $0xe,%edi
  401203:	e8 58 fb ff ff       	callq  400d60 <signal@plt>
  401208:	bf 05 00 00 00       	mov    $0x5,%edi
  40120d:	e8 0e fb ff ff       	callq  400d20 <alarm@plt>
  401212:	bd 1a 30 40 00       	mov    $0x40301a,%ebp
  401217:	eb 05                	jmp    40121e <main+0x69>
  401219:	bd 15 30 40 00       	mov    $0x403015,%ebp
  40121e:	48 8b 05 9b 32 20 00 	mov    0x20329b(%rip),%rax        # 6044c0 <stdin@@GLIBC_2.2.5>
  401225:	48 89 05 e4 32 20 00 	mov    %rax,0x2032e4(%rip)        # 604510 <infile>
  40122c:	41 bd 00 00 00 00    	mov    $0x0,%r13d
  401232:	41 be 00 00 00 00    	mov    $0x0,%r14d
  401238:	e9 c6 00 00 00       	jmpq   401303 <main+0x14e>
  40123d:	83 e8 61             	sub    $0x61,%eax
  401240:	3c 10                	cmp    $0x10,%al
  401242:	0f 87 9c 00 00 00    	ja     4012e4 <main+0x12f>
  401248:	0f b6 c0             	movzbl %al,%eax
  40124b:	ff 24 c5 60 30 40 00 	jmpq   *0x403060(,%rax,8)
  401252:	48 8b 3b             	mov    (%rbx),%rdi
  401255:	e8 4c fd ff ff       	callq  400fa6 <usage>
  40125a:	be dd 32 40 00       	mov    $0x4032dd,%esi
  40125f:	48 8b 3d 62 32 20 00 	mov    0x203262(%rip),%rdi        # 6044c8 <optarg@@GLIBC_2.2.5>
  401266:	e8 a5 fb ff ff       	callq  400e10 <fopen@plt>
  40126b:	48 89 05 9e 32 20 00 	mov    %rax,0x20329e(%rip)        # 604510 <infile>
  401272:	48 85 c0             	test   %rax,%rax
  401275:	0f 85 88 00 00 00    	jne    401303 <main+0x14e>
  40127b:	48 8b 0d 46 32 20 00 	mov    0x203246(%rip),%rcx        # 6044c8 <optarg@@GLIBC_2.2.5>
  401282:	ba 22 30 40 00       	mov    $0x403022,%edx
  401287:	be 01 00 00 00       	mov    $0x1,%esi
  40128c:	48 8b 3d 4d 32 20 00 	mov    0x20324d(%rip),%rdi        # 6044e0 <stderr@@GLIBC_2.2.5>
  401293:	e8 d8 fb ff ff       	callq  400e70 <__fprintf_chk@plt>
  401298:	b8 01 00 00 00       	mov    $0x1,%eax
  40129d:	e9 e4 00 00 00       	jmpq   401386 <main+0x1d1>
  4012a2:	ba 10 00 00 00       	mov    $0x10,%edx
  4012a7:	be 00 00 00 00       	mov    $0x0,%esi
  4012ac:	48 8b 3d 15 32 20 00 	mov    0x203215(%rip),%rdi        # 6044c8 <optarg@@GLIBC_2.2.5>
  4012b3:	e8 78 fb ff ff       	callq  400e30 <strtoul@plt>
  4012b8:	41 89 c6             	mov    %eax,%r14d
  4012bb:	eb 46                	jmp    401303 <main+0x14e>
  4012bd:	ba 0a 00 00 00       	mov    $0xa,%edx
  4012c2:	be 00 00 00 00       	mov    $0x0,%esi
  4012c7:	48 8b 3d fa 31 20 00 	mov    0x2031fa(%rip),%rdi        # 6044c8 <optarg@@GLIBC_2.2.5>
  4012ce:	e8 bd fa ff ff       	callq  400d90 <strtol@plt>
  4012d3:	41 89 c5             	mov    %eax,%r13d
  4012d6:	eb 2b                	jmp    401303 <main+0x14e>
  4012d8:	c7 05 c6 31 20 00 00 	movl   $0x0,0x2031c6(%rip)        # 6044a8 <notify>
  4012df:	00 00 00 
  4012e2:	eb 1f                	jmp    401303 <main+0x14e>
  4012e4:	0f be d2             	movsbl %dl,%edx
  4012e7:	be 3f 30 40 00       	mov    $0x40303f,%esi
  4012ec:	bf 01 00 00 00       	mov    $0x1,%edi
  4012f1:	b8 00 00 00 00       	mov    $0x0,%eax
  4012f6:	e8 05 fb ff ff       	callq  400e00 <__printf_chk@plt>
  4012fb:	48 8b 3b             	mov    (%rbx),%rdi
  4012fe:	e8 a3 fc ff ff       	callq  400fa6 <usage>
  401303:	48 89 ea             	mov    %rbp,%rdx
  401306:	48 89 de             	mov    %rbx,%rsi
  401309:	44 89 e7             	mov    %r12d,%edi
  40130c:	e8 0f fb ff ff       	callq  400e20 <getopt@plt>
  401311:	89 c2                	mov    %eax,%edx
  401313:	3c ff                	cmp    $0xff,%al
  401315:	0f 85 22 ff ff ff    	jne    40123d <main+0x88>
  40131b:	be 00 00 00 00       	mov    $0x0,%esi
  401320:	44 89 ef             	mov    %r13d,%edi
  401323:	e8 08 fd ff ff       	callq  401030 <initialize_target>
  401328:	83 3d f9 31 20 00 00 	cmpl   $0x0,0x2031f9(%rip)        # 604528 <is_checker>
  40132f:	74 2a                	je     40135b <main+0x1a6>
  401331:	44 3b 35 e8 31 20 00 	cmp    0x2031e8(%rip),%r14d        # 604520 <authkey>
  401338:	74 21                	je     40135b <main+0x1a6>
  40133a:	44 89 f2             	mov    %r14d,%edx
  40133d:	be 78 2f 40 00       	mov    $0x402f78,%esi
  401342:	bf 01 00 00 00       	mov    $0x1,%edi
  401347:	b8 00 00 00 00       	mov    $0x0,%eax
  40134c:	e8 af fa ff ff       	callq  400e00 <__printf_chk@plt>
  401351:	b8 00 00 00 00       	mov    $0x0,%eax
  401356:	e8 e9 06 00 00       	callq  401a44 <check_fail>
  40135b:	8b 15 c3 31 20 00    	mov    0x2031c3(%rip),%edx        # 604524 <cookie>
  401361:	be 52 30 40 00       	mov    $0x403052,%esi
  401366:	bf 01 00 00 00       	mov    $0x1,%edi
  40136b:	b8 00 00 00 00       	mov    $0x0,%eax
  401370:	e8 8b fa ff ff       	callq  400e00 <__printf_chk@plt>
  401375:	48 8b 3d 24 31 20 00 	mov    0x203124(%rip),%rdi        # 6044a0 <buf_offset>
  40137c:	e8 11 0c 00 00       	callq  401f92 <stable_launch>
  401381:	b8 00 00 00 00       	mov    $0x0,%eax
  401386:	5b                   	pop    %rbx
  401387:	5d                   	pop    %rbp
  401388:	41 5c                	pop    %r12
  40138a:	41 5d                	pop    %r13
  40138c:	41 5e                	pop    %r14
  40138e:	c3                   	retq   

000000000040138f <scramble>:
  40138f:	48 83 ec 38          	sub    $0x38,%rsp
  401393:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40139a:	00 00 
  40139c:	48 89 44 24 28       	mov    %rax,0x28(%rsp)
  4013a1:	31 c0                	xor    %eax,%eax
  4013a3:	eb 10                	jmp    4013b5 <scramble+0x26>
  4013a5:	69 d0 f9 55 00 00    	imul   $0x55f9,%eax,%edx
  4013ab:	01 fa                	add    %edi,%edx
  4013ad:	89 c1                	mov    %eax,%ecx
  4013af:	89 14 8c             	mov    %edx,(%rsp,%rcx,4)
  4013b2:	83 c0 01             	add    $0x1,%eax
  4013b5:	83 f8 09             	cmp    $0x9,%eax
  4013b8:	76 eb                	jbe    4013a5 <scramble+0x16>
  4013ba:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  4013be:	69 c0 f5 3b 00 00    	imul   $0x3bf5,%eax,%eax
  4013c4:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  4013c8:	8b 44 24 04          	mov    0x4(%rsp),%eax
  4013cc:	69 c0 cd 5f 00 00    	imul   $0x5fcd,%eax,%eax
  4013d2:	89 44 24 04          	mov    %eax,0x4(%rsp)
  4013d6:	8b 44 24 04          	mov    0x4(%rsp),%eax
  4013da:	69 c0 34 03 00 00    	imul   $0x334,%eax,%eax
  4013e0:	89 44 24 04          	mov    %eax,0x4(%rsp)
  4013e4:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  4013e8:	69 c0 fe 8d 00 00    	imul   $0x8dfe,%eax,%eax
  4013ee:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  4013f2:	8b 44 24 24          	mov    0x24(%rsp),%eax
  4013f6:	69 c0 0a 4b 00 00    	imul   $0x4b0a,%eax,%eax
  4013fc:	89 44 24 24          	mov    %eax,0x24(%rsp)
  401400:	8b 44 24 18          	mov    0x18(%rsp),%eax
  401404:	69 c0 26 44 00 00    	imul   $0x4426,%eax,%eax
  40140a:	89 44 24 18          	mov    %eax,0x18(%rsp)
  40140e:	8b 04 24             	mov    (%rsp),%eax
  401411:	69 c0 49 38 00 00    	imul   $0x3849,%eax,%eax
  401417:	89 04 24             	mov    %eax,(%rsp)
  40141a:	8b 44 24 24          	mov    0x24(%rsp),%eax
  40141e:	69 c0 4f bc 00 00    	imul   $0xbc4f,%eax,%eax
  401424:	89 44 24 24          	mov    %eax,0x24(%rsp)
  401428:	8b 44 24 24          	mov    0x24(%rsp),%eax
  40142c:	69 c0 55 0c 00 00    	imul   $0xc55,%eax,%eax
  401432:	89 44 24 24          	mov    %eax,0x24(%rsp)
  401436:	8b 44 24 14          	mov    0x14(%rsp),%eax
  40143a:	69 c0 00 b2 00 00    	imul   $0xb200,%eax,%eax
  401440:	89 44 24 14          	mov    %eax,0x14(%rsp)
  401444:	8b 04 24             	mov    (%rsp),%eax
  401447:	69 c0 32 93 00 00    	imul   $0x9332,%eax,%eax
  40144d:	89 04 24             	mov    %eax,(%rsp)
  401450:	8b 44 24 14          	mov    0x14(%rsp),%eax
  401454:	69 c0 7f 37 00 00    	imul   $0x377f,%eax,%eax
  40145a:	89 44 24 14          	mov    %eax,0x14(%rsp)
  40145e:	8b 44 24 14          	mov    0x14(%rsp),%eax
  401462:	69 c0 93 27 00 00    	imul   $0x2793,%eax,%eax
  401468:	89 44 24 14          	mov    %eax,0x14(%rsp)
  40146c:	8b 44 24 14          	mov    0x14(%rsp),%eax
  401470:	69 c0 15 02 00 00    	imul   $0x215,%eax,%eax
  401476:	89 44 24 14          	mov    %eax,0x14(%rsp)
  40147a:	8b 44 24 04          	mov    0x4(%rsp),%eax
  40147e:	69 c0 d2 2a 00 00    	imul   $0x2ad2,%eax,%eax
  401484:	89 44 24 04          	mov    %eax,0x4(%rsp)
  401488:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  40148c:	69 c0 f2 26 00 00    	imul   $0x26f2,%eax,%eax
  401492:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  401496:	8b 44 24 10          	mov    0x10(%rsp),%eax
  40149a:	69 c0 4e c2 00 00    	imul   $0xc24e,%eax,%eax
  4014a0:	89 44 24 10          	mov    %eax,0x10(%rsp)
  4014a4:	8b 44 24 20          	mov    0x20(%rsp),%eax
  4014a8:	69 c0 b5 d4 00 00    	imul   $0xd4b5,%eax,%eax
  4014ae:	89 44 24 20          	mov    %eax,0x20(%rsp)
  4014b2:	8b 44 24 14          	mov    0x14(%rsp),%eax
  4014b6:	69 c0 cf 6e 00 00    	imul   $0x6ecf,%eax,%eax
  4014bc:	89 44 24 14          	mov    %eax,0x14(%rsp)
  4014c0:	8b 44 24 24          	mov    0x24(%rsp),%eax
  4014c4:	69 c0 b9 07 00 00    	imul   $0x7b9,%eax,%eax
  4014ca:	89 44 24 24          	mov    %eax,0x24(%rsp)
  4014ce:	8b 04 24             	mov    (%rsp),%eax
  4014d1:	69 c0 6c 5a 00 00    	imul   $0x5a6c,%eax,%eax
  4014d7:	89 04 24             	mov    %eax,(%rsp)
  4014da:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  4014de:	69 c0 c1 ed 00 00    	imul   $0xedc1,%eax,%eax
  4014e4:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  4014e8:	8b 44 24 08          	mov    0x8(%rsp),%eax
  4014ec:	69 c0 6c f1 00 00    	imul   $0xf16c,%eax,%eax
  4014f2:	89 44 24 08          	mov    %eax,0x8(%rsp)
  4014f6:	8b 44 24 20          	mov    0x20(%rsp),%eax
  4014fa:	69 c0 bf fb 00 00    	imul   $0xfbbf,%eax,%eax
  401500:	89 44 24 20          	mov    %eax,0x20(%rsp)
  401504:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401508:	69 c0 b9 04 00 00    	imul   $0x4b9,%eax,%eax
  40150e:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  401512:	8b 44 24 18          	mov    0x18(%rsp),%eax
  401516:	69 c0 cd 45 00 00    	imul   $0x45cd,%eax,%eax
  40151c:	89 44 24 18          	mov    %eax,0x18(%rsp)
  401520:	8b 44 24 04          	mov    0x4(%rsp),%eax
  401524:	69 c0 c9 ae 00 00    	imul   $0xaec9,%eax,%eax
  40152a:	89 44 24 04          	mov    %eax,0x4(%rsp)
  40152e:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401532:	69 c0 dd d7 00 00    	imul   $0xd7dd,%eax,%eax
  401538:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  40153c:	8b 44 24 04          	mov    0x4(%rsp),%eax
  401540:	69 c0 fa d0 00 00    	imul   $0xd0fa,%eax,%eax
  401546:	89 44 24 04          	mov    %eax,0x4(%rsp)
  40154a:	8b 44 24 08          	mov    0x8(%rsp),%eax
  40154e:	69 c0 56 a7 00 00    	imul   $0xa756,%eax,%eax
  401554:	89 44 24 08          	mov    %eax,0x8(%rsp)
  401558:	8b 44 24 24          	mov    0x24(%rsp),%eax
  40155c:	69 c0 bc 7f 00 00    	imul   $0x7fbc,%eax,%eax
  401562:	89 44 24 24          	mov    %eax,0x24(%rsp)
  401566:	8b 44 24 10          	mov    0x10(%rsp),%eax
  40156a:	69 c0 93 62 00 00    	imul   $0x6293,%eax,%eax
  401570:	89 44 24 10          	mov    %eax,0x10(%rsp)
  401574:	8b 04 24             	mov    (%rsp),%eax
  401577:	69 c0 09 55 00 00    	imul   $0x5509,%eax,%eax
  40157d:	89 04 24             	mov    %eax,(%rsp)
  401580:	8b 44 24 08          	mov    0x8(%rsp),%eax
  401584:	69 c0 8c 07 00 00    	imul   $0x78c,%eax,%eax
  40158a:	89 44 24 08          	mov    %eax,0x8(%rsp)
  40158e:	8b 44 24 10          	mov    0x10(%rsp),%eax
  401592:	69 c0 fb 99 00 00    	imul   $0x99fb,%eax,%eax
  401598:	89 44 24 10          	mov    %eax,0x10(%rsp)
  40159c:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  4015a0:	69 c0 b1 7d 00 00    	imul   $0x7db1,%eax,%eax
  4015a6:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  4015aa:	8b 44 24 18          	mov    0x18(%rsp),%eax
  4015ae:	69 c0 26 5b 00 00    	imul   $0x5b26,%eax,%eax
  4015b4:	89 44 24 18          	mov    %eax,0x18(%rsp)
  4015b8:	8b 44 24 10          	mov    0x10(%rsp),%eax
  4015bc:	69 c0 1d 87 00 00    	imul   $0x871d,%eax,%eax
  4015c2:	89 44 24 10          	mov    %eax,0x10(%rsp)
  4015c6:	8b 04 24             	mov    (%rsp),%eax
  4015c9:	69 c0 83 15 00 00    	imul   $0x1583,%eax,%eax
  4015cf:	89 04 24             	mov    %eax,(%rsp)
  4015d2:	8b 44 24 18          	mov    0x18(%rsp),%eax
  4015d6:	69 c0 54 4a 00 00    	imul   $0x4a54,%eax,%eax
  4015dc:	89 44 24 18          	mov    %eax,0x18(%rsp)
  4015e0:	8b 04 24             	mov    (%rsp),%eax
  4015e3:	69 c0 9b 30 00 00    	imul   $0x309b,%eax,%eax
  4015e9:	89 04 24             	mov    %eax,(%rsp)
  4015ec:	8b 44 24 24          	mov    0x24(%rsp),%eax
  4015f0:	69 c0 28 b2 00 00    	imul   $0xb228,%eax,%eax
  4015f6:	89 44 24 24          	mov    %eax,0x24(%rsp)
  4015fa:	8b 44 24 18          	mov    0x18(%rsp),%eax
  4015fe:	69 c0 6f 0d 00 00    	imul   $0xd6f,%eax,%eax
  401604:	89 44 24 18          	mov    %eax,0x18(%rsp)
  401608:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  40160c:	69 c0 c2 b5 00 00    	imul   $0xb5c2,%eax,%eax
  401612:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  401616:	8b 44 24 08          	mov    0x8(%rsp),%eax
  40161a:	69 c0 f9 63 00 00    	imul   $0x63f9,%eax,%eax
  401620:	89 44 24 08          	mov    %eax,0x8(%rsp)
  401624:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  401628:	69 c0 35 da 00 00    	imul   $0xda35,%eax,%eax
  40162e:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  401632:	8b 44 24 18          	mov    0x18(%rsp),%eax
  401636:	69 c0 61 2b 00 00    	imul   $0x2b61,%eax,%eax
  40163c:	89 44 24 18          	mov    %eax,0x18(%rsp)
  401640:	8b 44 24 18          	mov    0x18(%rsp),%eax
  401644:	69 c0 bf 25 00 00    	imul   $0x25bf,%eax,%eax
  40164a:	89 44 24 18          	mov    %eax,0x18(%rsp)
  40164e:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  401652:	69 c0 11 74 00 00    	imul   $0x7411,%eax,%eax
  401658:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  40165c:	8b 44 24 18          	mov    0x18(%rsp),%eax
  401660:	69 c0 42 44 00 00    	imul   $0x4442,%eax,%eax
  401666:	89 44 24 18          	mov    %eax,0x18(%rsp)
  40166a:	8b 44 24 24          	mov    0x24(%rsp),%eax
  40166e:	69 c0 91 3c 00 00    	imul   $0x3c91,%eax,%eax
  401674:	89 44 24 24          	mov    %eax,0x24(%rsp)
  401678:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  40167c:	69 c0 74 02 00 00    	imul   $0x274,%eax,%eax
  401682:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  401686:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  40168a:	69 c0 66 2d 00 00    	imul   $0x2d66,%eax,%eax
  401690:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  401694:	8b 44 24 04          	mov    0x4(%rsp),%eax
  401698:	69 c0 4a e4 00 00    	imul   $0xe44a,%eax,%eax
  40169e:	89 44 24 04          	mov    %eax,0x4(%rsp)
  4016a2:	8b 44 24 18          	mov    0x18(%rsp),%eax
  4016a6:	69 c0 6d 0c 00 00    	imul   $0xc6d,%eax,%eax
  4016ac:	89 44 24 18          	mov    %eax,0x18(%rsp)
  4016b0:	8b 44 24 10          	mov    0x10(%rsp),%eax
  4016b4:	69 c0 25 5d 00 00    	imul   $0x5d25,%eax,%eax
  4016ba:	89 44 24 10          	mov    %eax,0x10(%rsp)
  4016be:	8b 44 24 08          	mov    0x8(%rsp),%eax
  4016c2:	69 c0 c0 be 00 00    	imul   $0xbec0,%eax,%eax
  4016c8:	89 44 24 08          	mov    %eax,0x8(%rsp)
  4016cc:	8b 44 24 04          	mov    0x4(%rsp),%eax
  4016d0:	69 c0 6d 1c 00 00    	imul   $0x1c6d,%eax,%eax
  4016d6:	89 44 24 04          	mov    %eax,0x4(%rsp)
  4016da:	8b 44 24 0c          	mov    0xc(%rsp),%eax
  4016de:	69 c0 54 99 00 00    	imul   $0x9954,%eax,%eax
  4016e4:	89 44 24 0c          	mov    %eax,0xc(%rsp)
  4016e8:	8b 44 24 24          	mov    0x24(%rsp),%eax
  4016ec:	69 c0 98 aa 00 00    	imul   $0xaa98,%eax,%eax
  4016f2:	89 44 24 24          	mov    %eax,0x24(%rsp)
  4016f6:	8b 44 24 04          	mov    0x4(%rsp),%eax
  4016fa:	69 c0 48 2f 00 00    	imul   $0x2f48,%eax,%eax
  401700:	89 44 24 04          	mov    %eax,0x4(%rsp)
  401704:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401708:	69 c0 02 e1 00 00    	imul   $0xe102,%eax,%eax
  40170e:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  401712:	8b 44 24 04          	mov    0x4(%rsp),%eax
  401716:	69 c0 96 c1 00 00    	imul   $0xc196,%eax,%eax
  40171c:	89 44 24 04          	mov    %eax,0x4(%rsp)
  401720:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  401724:	69 c0 14 db 00 00    	imul   $0xdb14,%eax,%eax
  40172a:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  40172e:	8b 44 24 10          	mov    0x10(%rsp),%eax
  401732:	69 c0 0c 34 00 00    	imul   $0x340c,%eax,%eax
  401738:	89 44 24 10          	mov    %eax,0x10(%rsp)
  40173c:	8b 44 24 18          	mov    0x18(%rsp),%eax
  401740:	69 c0 b3 43 00 00    	imul   $0x43b3,%eax,%eax
  401746:	89 44 24 18          	mov    %eax,0x18(%rsp)
  40174a:	8b 44 24 14          	mov    0x14(%rsp),%eax
  40174e:	69 c0 4a e1 00 00    	imul   $0xe14a,%eax,%eax
  401754:	89 44 24 14          	mov    %eax,0x14(%rsp)
  401758:	8b 44 24 10          	mov    0x10(%rsp),%eax
  40175c:	69 c0 55 08 00 00    	imul   $0x855,%eax,%eax
  401762:	89 44 24 10          	mov    %eax,0x10(%rsp)
  401766:	8b 44 24 04          	mov    0x4(%rsp),%eax
  40176a:	69 c0 b8 cf 00 00    	imul   $0xcfb8,%eax,%eax
  401770:	89 44 24 04          	mov    %eax,0x4(%rsp)
  401774:	8b 44 24 14          	mov    0x14(%rsp),%eax
  401778:	69 c0 99 51 00 00    	imul   $0x5199,%eax,%eax
  40177e:	89 44 24 14          	mov    %eax,0x14(%rsp)
  401782:	8b 44 24 10          	mov    0x10(%rsp),%eax
  401786:	69 c0 3e 1b 00 00    	imul   $0x1b3e,%eax,%eax
  40178c:	89 44 24 10          	mov    %eax,0x10(%rsp)
  401790:	8b 44 24 18          	mov    0x18(%rsp),%eax
  401794:	69 c0 2e 19 00 00    	imul   $0x192e,%eax,%eax
  40179a:	89 44 24 18          	mov    %eax,0x18(%rsp)
  40179e:	8b 44 24 1c          	mov    0x1c(%rsp),%eax
  4017a2:	69 c0 0c be 00 00    	imul   $0xbe0c,%eax,%eax
  4017a8:	89 44 24 1c          	mov    %eax,0x1c(%rsp)
  4017ac:	8b 44 24 20          	mov    0x20(%rsp),%eax
  4017b0:	69 c0 2e a6 00 00    	imul   $0xa62e,%eax,%eax
  4017b6:	89 44 24 20          	mov    %eax,0x20(%rsp)
  4017ba:	ba 00 00 00 00       	mov    $0x0,%edx
  4017bf:	b8 00 00 00 00       	mov    $0x0,%eax
  4017c4:	eb 0a                	jmp    4017d0 <scramble+0x441>
  4017c6:	89 d1                	mov    %edx,%ecx
  4017c8:	8b 0c 8c             	mov    (%rsp,%rcx,4),%ecx
  4017cb:	01 c8                	add    %ecx,%eax
  4017cd:	83 c2 01             	add    $0x1,%edx
  4017d0:	83 fa 09             	cmp    $0x9,%edx
  4017d3:	76 f1                	jbe    4017c6 <scramble+0x437>
  4017d5:	48 8b 74 24 28       	mov    0x28(%rsp),%rsi
  4017da:	64 48 33 34 25 28 00 	xor    %fs:0x28,%rsi
  4017e1:	00 00 
  4017e3:	74 05                	je     4017ea <scramble+0x45b>
  4017e5:	e8 06 f5 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  4017ea:	48 83 c4 38          	add    $0x38,%rsp
  4017ee:	c3                   	retq   

00000000004017ef <getbuf>:
  4017ef:	48 83 ec 38          	sub    $0x38,%rsp
  4017f3:	48 89 e7             	mov    %rsp,%rdi
  4017f6:	e8 7e 02 00 00       	callq  401a79 <Gets>
  4017fb:	b8 01 00 00 00       	mov    $0x1,%eax
  401800:	48 83 c4 38          	add    $0x38,%rsp
  401804:	c3                   	retq   

0000000000401805 <touch1>:
  401805:	48 83 ec 08          	sub    $0x8,%rsp
  401809:	c7 05 09 2d 20 00 01 	movl   $0x1,0x202d09(%rip)        # 60451c <vlevel>
  401810:	00 00 00 
  401813:	bf 35 31 40 00       	mov    $0x403135,%edi
  401818:	e8 b3 f4 ff ff       	callq  400cd0 <puts@plt>
  40181d:	bf 01 00 00 00       	mov    $0x1,%edi
  401822:	e8 97 04 00 00       	callq  401cbe <validate>
  401827:	bf 00 00 00 00       	mov    $0x0,%edi
  40182c:	e8 1f f6 ff ff       	callq  400e50 <exit@plt>

0000000000401831 <touch2>:
  401831:	48 83 ec 08          	sub    $0x8,%rsp
  401835:	89 fa                	mov    %edi,%edx
  401837:	c7 05 db 2c 20 00 02 	movl   $0x2,0x202cdb(%rip)        # 60451c <vlevel>
  40183e:	00 00 00 
  401841:	39 3d dd 2c 20 00    	cmp    %edi,0x202cdd(%rip)        # 604524 <cookie>
  401847:	75 20                	jne    401869 <touch2+0x38>
  401849:	be 58 31 40 00       	mov    $0x403158,%esi
  40184e:	bf 01 00 00 00       	mov    $0x1,%edi
  401853:	b8 00 00 00 00       	mov    $0x0,%eax
  401858:	e8 a3 f5 ff ff       	callq  400e00 <__printf_chk@plt>
  40185d:	bf 02 00 00 00       	mov    $0x2,%edi
  401862:	e8 57 04 00 00       	callq  401cbe <validate>
  401867:	eb 1e                	jmp    401887 <touch2+0x56>
  401869:	be 80 31 40 00       	mov    $0x403180,%esi
  40186e:	bf 01 00 00 00       	mov    $0x1,%edi
  401873:	b8 00 00 00 00       	mov    $0x0,%eax
  401878:	e8 83 f5 ff ff       	callq  400e00 <__printf_chk@plt>
  40187d:	bf 02 00 00 00       	mov    $0x2,%edi
  401882:	e8 f9 04 00 00       	callq  401d80 <fail>
  401887:	bf 00 00 00 00       	mov    $0x0,%edi
  40188c:	e8 bf f5 ff ff       	callq  400e50 <exit@plt>

0000000000401891 <hexmatch>:
  401891:	41 54                	push   %r12
  401893:	55                   	push   %rbp
  401894:	53                   	push   %rbx
  401895:	48 83 c4 80          	add    $0xffffffffffffff80,%rsp
  401899:	89 fd                	mov    %edi,%ebp
  40189b:	48 89 f3             	mov    %rsi,%rbx
  40189e:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4018a5:	00 00 
  4018a7:	48 89 44 24 78       	mov    %rax,0x78(%rsp)
  4018ac:	31 c0                	xor    %eax,%eax
  4018ae:	e8 0d f5 ff ff       	callq  400dc0 <random@plt>
  4018b3:	48 89 c1             	mov    %rax,%rcx
  4018b6:	48 ba 0b d7 a3 70 3d 	movabs $0xa3d70a3d70a3d70b,%rdx
  4018bd:	0a d7 a3 
  4018c0:	48 f7 ea             	imul   %rdx
  4018c3:	48 01 ca             	add    %rcx,%rdx
  4018c6:	48 c1 fa 06          	sar    $0x6,%rdx
  4018ca:	48 89 c8             	mov    %rcx,%rax
  4018cd:	48 c1 f8 3f          	sar    $0x3f,%rax
  4018d1:	48 29 c2             	sub    %rax,%rdx
  4018d4:	48 8d 04 92          	lea    (%rdx,%rdx,4),%rax
  4018d8:	48 8d 14 80          	lea    (%rax,%rax,4),%rdx
  4018dc:	48 8d 04 95 00 00 00 	lea    0x0(,%rdx,4),%rax
  4018e3:	00 
  4018e4:	48 29 c1             	sub    %rax,%rcx
  4018e7:	4c 8d 24 0c          	lea    (%rsp,%rcx,1),%r12
  4018eb:	41 89 e8             	mov    %ebp,%r8d
  4018ee:	b9 52 31 40 00       	mov    $0x403152,%ecx
  4018f3:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  4018fa:	be 01 00 00 00       	mov    $0x1,%esi
  4018ff:	4c 89 e7             	mov    %r12,%rdi
  401902:	b8 00 00 00 00       	mov    $0x0,%eax
  401907:	e8 74 f5 ff ff       	callq  400e80 <__sprintf_chk@plt>
  40190c:	ba 09 00 00 00       	mov    $0x9,%edx
  401911:	4c 89 e6             	mov    %r12,%rsi
  401914:	48 89 df             	mov    %rbx,%rdi
  401917:	e8 94 f3 ff ff       	callq  400cb0 <strncmp@plt>
  40191c:	85 c0                	test   %eax,%eax
  40191e:	0f 94 c0             	sete   %al
  401921:	48 8b 5c 24 78       	mov    0x78(%rsp),%rbx
  401926:	64 48 33 1c 25 28 00 	xor    %fs:0x28,%rbx
  40192d:	00 00 
  40192f:	74 05                	je     401936 <hexmatch+0xa5>
  401931:	e8 ba f3 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  401936:	0f b6 c0             	movzbl %al,%eax
  401939:	48 83 ec 80          	sub    $0xffffffffffffff80,%rsp
  40193d:	5b                   	pop    %rbx
  40193e:	5d                   	pop    %rbp
  40193f:	41 5c                	pop    %r12
  401941:	c3                   	retq   

0000000000401942 <touch3>:
  401942:	53                   	push   %rbx
  401943:	48 89 fb             	mov    %rdi,%rbx
  401946:	c7 05 cc 2b 20 00 03 	movl   $0x3,0x202bcc(%rip)        # 60451c <vlevel>
  40194d:	00 00 00 
  401950:	48 89 fe             	mov    %rdi,%rsi
  401953:	8b 3d cb 2b 20 00    	mov    0x202bcb(%rip),%edi        # 604524 <cookie>
  401959:	e8 33 ff ff ff       	callq  401891 <hexmatch>
  40195e:	85 c0                	test   %eax,%eax
  401960:	74 23                	je     401985 <touch3+0x43>
  401962:	48 89 da             	mov    %rbx,%rdx
  401965:	be a8 31 40 00       	mov    $0x4031a8,%esi
  40196a:	bf 01 00 00 00       	mov    $0x1,%edi
  40196f:	b8 00 00 00 00       	mov    $0x0,%eax
  401974:	e8 87 f4 ff ff       	callq  400e00 <__printf_chk@plt>
  401979:	bf 03 00 00 00       	mov    $0x3,%edi
  40197e:	e8 3b 03 00 00       	callq  401cbe <validate>
  401983:	eb 21                	jmp    4019a6 <touch3+0x64>
  401985:	48 89 da             	mov    %rbx,%rdx
  401988:	be d0 31 40 00       	mov    $0x4031d0,%esi
  40198d:	bf 01 00 00 00       	mov    $0x1,%edi
  401992:	b8 00 00 00 00       	mov    $0x0,%eax
  401997:	e8 64 f4 ff ff       	callq  400e00 <__printf_chk@plt>
  40199c:	bf 03 00 00 00       	mov    $0x3,%edi
  4019a1:	e8 da 03 00 00       	callq  401d80 <fail>
  4019a6:	bf 00 00 00 00       	mov    $0x0,%edi
  4019ab:	e8 a0 f4 ff ff       	callq  400e50 <exit@plt>

00000000004019b0 <test>:
  4019b0:	48 83 ec 08          	sub    $0x8,%rsp
  4019b4:	b8 00 00 00 00       	mov    $0x0,%eax
  4019b9:	e8 31 fe ff ff       	callq  4017ef <getbuf>
  4019be:	89 c2                	mov    %eax,%edx
  4019c0:	be f8 31 40 00       	mov    $0x4031f8,%esi
  4019c5:	bf 01 00 00 00       	mov    $0x1,%edi
  4019ca:	b8 00 00 00 00       	mov    $0x0,%eax
  4019cf:	e8 2c f4 ff ff       	callq  400e00 <__printf_chk@plt>
  4019d4:	48 83 c4 08          	add    $0x8,%rsp
  4019d8:	c3                   	retq   

00000000004019d9 <save_char>:
  4019d9:	8b 05 65 37 20 00    	mov    0x203765(%rip),%eax        # 605144 <gets_cnt>
  4019df:	3d ff 03 00 00       	cmp    $0x3ff,%eax
  4019e4:	7f 49                	jg     401a2f <save_char+0x56>
  4019e6:	8d 14 40             	lea    (%rax,%rax,2),%edx
  4019e9:	89 f9                	mov    %edi,%ecx
  4019eb:	c0 e9 04             	shr    $0x4,%cl
  4019ee:	83 e1 0f             	and    $0xf,%ecx
  4019f1:	0f b6 b1 20 35 40 00 	movzbl 0x403520(%rcx),%esi
  4019f8:	48 63 ca             	movslq %edx,%rcx
  4019fb:	40 88 b1 40 45 60 00 	mov    %sil,0x604540(%rcx)
  401a02:	8d 4a 01             	lea    0x1(%rdx),%ecx
  401a05:	83 e7 0f             	and    $0xf,%edi
  401a08:	0f b6 b7 20 35 40 00 	movzbl 0x403520(%rdi),%esi
  401a0f:	48 63 c9             	movslq %ecx,%rcx
  401a12:	40 88 b1 40 45 60 00 	mov    %sil,0x604540(%rcx)
  401a19:	83 c2 02             	add    $0x2,%edx
  401a1c:	48 63 d2             	movslq %edx,%rdx
  401a1f:	c6 82 40 45 60 00 20 	movb   $0x20,0x604540(%rdx)
  401a26:	83 c0 01             	add    $0x1,%eax
  401a29:	89 05 15 37 20 00    	mov    %eax,0x203715(%rip)        # 605144 <gets_cnt>
  401a2f:	f3 c3                	repz retq 

0000000000401a31 <save_term>:
  401a31:	8b 05 0d 37 20 00    	mov    0x20370d(%rip),%eax        # 605144 <gets_cnt>
  401a37:	8d 04 40             	lea    (%rax,%rax,2),%eax
  401a3a:	48 98                	cltq   
  401a3c:	c6 80 40 45 60 00 00 	movb   $0x0,0x604540(%rax)
  401a43:	c3                   	retq   

0000000000401a44 <check_fail>:
  401a44:	48 83 ec 08          	sub    $0x8,%rsp
  401a48:	0f be 15 f9 36 20 00 	movsbl 0x2036f9(%rip),%edx        # 605148 <target_prefix>
  401a4f:	41 b8 40 45 60 00    	mov    $0x604540,%r8d
  401a55:	8b 0d bd 2a 20 00    	mov    0x202abd(%rip),%ecx        # 604518 <check_level>
  401a5b:	be 1b 32 40 00       	mov    $0x40321b,%esi
  401a60:	bf 01 00 00 00       	mov    $0x1,%edi
  401a65:	b8 00 00 00 00       	mov    $0x0,%eax
  401a6a:	e8 91 f3 ff ff       	callq  400e00 <__printf_chk@plt>
  401a6f:	bf 01 00 00 00       	mov    $0x1,%edi
  401a74:	e8 d7 f3 ff ff       	callq  400e50 <exit@plt>

0000000000401a79 <Gets>:
  401a79:	41 54                	push   %r12
  401a7b:	55                   	push   %rbp
  401a7c:	53                   	push   %rbx
  401a7d:	49 89 fc             	mov    %rdi,%r12
  401a80:	c7 05 ba 36 20 00 00 	movl   $0x0,0x2036ba(%rip)        # 605144 <gets_cnt>
  401a87:	00 00 00 
  401a8a:	48 89 fb             	mov    %rdi,%rbx
  401a8d:	eb 11                	jmp    401aa0 <Gets+0x27>
  401a8f:	48 8d 6b 01          	lea    0x1(%rbx),%rbp
  401a93:	88 03                	mov    %al,(%rbx)
  401a95:	0f b6 f8             	movzbl %al,%edi
  401a98:	e8 3c ff ff ff       	callq  4019d9 <save_char>
  401a9d:	48 89 eb             	mov    %rbp,%rbx
  401aa0:	48 8b 3d 69 2a 20 00 	mov    0x202a69(%rip),%rdi        # 604510 <infile>
  401aa7:	e8 24 f3 ff ff       	callq  400dd0 <_IO_getc@plt>
  401aac:	83 f8 ff             	cmp    $0xffffffff,%eax
  401aaf:	74 05                	je     401ab6 <Gets+0x3d>
  401ab1:	83 f8 0a             	cmp    $0xa,%eax
  401ab4:	75 d9                	jne    401a8f <Gets+0x16>
  401ab6:	c6 03 00             	movb   $0x0,(%rbx)
  401ab9:	b8 00 00 00 00       	mov    $0x0,%eax
  401abe:	e8 6e ff ff ff       	callq  401a31 <save_term>
  401ac3:	4c 89 e0             	mov    %r12,%rax
  401ac6:	5b                   	pop    %rbx
  401ac7:	5d                   	pop    %rbp
  401ac8:	41 5c                	pop    %r12
  401aca:	c3                   	retq   

0000000000401acb <notify_server>:
  401acb:	53                   	push   %rbx
  401acc:	48 81 ec 10 40 00 00 	sub    $0x4010,%rsp
  401ad3:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401ada:	00 00 
  401adc:	48 89 84 24 08 40 00 	mov    %rax,0x4008(%rsp)
  401ae3:	00 
  401ae4:	31 c0                	xor    %eax,%eax
  401ae6:	83 3d 3b 2a 20 00 00 	cmpl   $0x0,0x202a3b(%rip)        # 604528 <is_checker>
  401aed:	0f 85 aa 01 00 00    	jne    401c9d <notify_server+0x1d2>
  401af3:	89 fb                	mov    %edi,%ebx
  401af5:	8b 05 49 36 20 00    	mov    0x203649(%rip),%eax        # 605144 <gets_cnt>
  401afb:	83 c0 64             	add    $0x64,%eax
  401afe:	3d 00 20 00 00       	cmp    $0x2000,%eax
  401b03:	7e 1e                	jle    401b23 <notify_server+0x58>
  401b05:	be 50 33 40 00       	mov    $0x403350,%esi
  401b0a:	bf 01 00 00 00       	mov    $0x1,%edi
  401b0f:	b8 00 00 00 00       	mov    $0x0,%eax
  401b14:	e8 e7 f2 ff ff       	callq  400e00 <__printf_chk@plt>
  401b19:	bf 01 00 00 00       	mov    $0x1,%edi
  401b1e:	e8 2d f3 ff ff       	callq  400e50 <exit@plt>
  401b23:	0f be 05 1e 36 20 00 	movsbl 0x20361e(%rip),%eax        # 605148 <target_prefix>
  401b2a:	83 3d 77 29 20 00 00 	cmpl   $0x0,0x202977(%rip)        # 6044a8 <notify>
  401b31:	74 08                	je     401b3b <notify_server+0x70>
  401b33:	8b 15 e7 29 20 00    	mov    0x2029e7(%rip),%edx        # 604520 <authkey>
  401b39:	eb 05                	jmp    401b40 <notify_server+0x75>
  401b3b:	ba ff ff ff ff       	mov    $0xffffffff,%edx
  401b40:	85 db                	test   %ebx,%ebx
  401b42:	74 08                	je     401b4c <notify_server+0x81>
  401b44:	41 b9 31 32 40 00    	mov    $0x403231,%r9d
  401b4a:	eb 06                	jmp    401b52 <notify_server+0x87>
  401b4c:	41 b9 36 32 40 00    	mov    $0x403236,%r9d
  401b52:	68 40 45 60 00       	pushq  $0x604540
  401b57:	56                   	push   %rsi
  401b58:	50                   	push   %rax
  401b59:	52                   	push   %rdx
  401b5a:	44 8b 05 07 26 20 00 	mov    0x202607(%rip),%r8d        # 604168 <target_id>
  401b61:	b9 3b 32 40 00       	mov    $0x40323b,%ecx
  401b66:	ba 00 20 00 00       	mov    $0x2000,%edx
  401b6b:	be 01 00 00 00       	mov    $0x1,%esi
  401b70:	48 8d 7c 24 20       	lea    0x20(%rsp),%rdi
  401b75:	b8 00 00 00 00       	mov    $0x0,%eax
  401b7a:	e8 01 f3 ff ff       	callq  400e80 <__sprintf_chk@plt>
  401b7f:	48 83 c4 20          	add    $0x20,%rsp
  401b83:	83 3d 1e 29 20 00 00 	cmpl   $0x0,0x20291e(%rip)        # 6044a8 <notify>
  401b8a:	0f 84 81 00 00 00    	je     401c11 <notify_server+0x146>
  401b90:	85 db                	test   %ebx,%ebx
  401b92:	74 6e                	je     401c02 <notify_server+0x137>
  401b94:	4c 8d 8c 24 00 20 00 	lea    0x2000(%rsp),%r9
  401b9b:	00 
  401b9c:	41 b8 00 00 00 00    	mov    $0x0,%r8d
  401ba2:	48 89 e1             	mov    %rsp,%rcx
  401ba5:	48 8b 15 c4 25 20 00 	mov    0x2025c4(%rip),%rdx        # 604170 <lab>
  401bac:	48 8b 35 c5 25 20 00 	mov    0x2025c5(%rip),%rsi        # 604178 <course>
  401bb3:	48 8b 3d a6 25 20 00 	mov    0x2025a6(%rip),%rdi        # 604160 <user_id>
  401bba:	e8 ef 10 00 00       	callq  402cae <driver_post>
  401bbf:	85 c0                	test   %eax,%eax
  401bc1:	79 26                	jns    401be9 <notify_server+0x11e>
  401bc3:	48 8d 94 24 00 20 00 	lea    0x2000(%rsp),%rdx
  401bca:	00 
  401bcb:	be 57 32 40 00       	mov    $0x403257,%esi
  401bd0:	bf 01 00 00 00       	mov    $0x1,%edi
  401bd5:	b8 00 00 00 00       	mov    $0x0,%eax
  401bda:	e8 21 f2 ff ff       	callq  400e00 <__printf_chk@plt>
  401bdf:	bf 01 00 00 00       	mov    $0x1,%edi
  401be4:	e8 67 f2 ff ff       	callq  400e50 <exit@plt>
  401be9:	bf 80 33 40 00       	mov    $0x403380,%edi
  401bee:	e8 dd f0 ff ff       	callq  400cd0 <puts@plt>
  401bf3:	bf 63 32 40 00       	mov    $0x403263,%edi
  401bf8:	e8 d3 f0 ff ff       	callq  400cd0 <puts@plt>
  401bfd:	e9 9b 00 00 00       	jmpq   401c9d <notify_server+0x1d2>
  401c02:	bf 6d 32 40 00       	mov    $0x40326d,%edi
  401c07:	e8 c4 f0 ff ff       	callq  400cd0 <puts@plt>
  401c0c:	e9 8c 00 00 00       	jmpq   401c9d <notify_server+0x1d2>
  401c11:	85 db                	test   %ebx,%ebx
  401c13:	74 07                	je     401c1c <notify_server+0x151>
  401c15:	ba 31 32 40 00       	mov    $0x403231,%edx
  401c1a:	eb 05                	jmp    401c21 <notify_server+0x156>
  401c1c:	ba 36 32 40 00       	mov    $0x403236,%edx
  401c21:	be b8 33 40 00       	mov    $0x4033b8,%esi
  401c26:	bf 01 00 00 00       	mov    $0x1,%edi
  401c2b:	b8 00 00 00 00       	mov    $0x0,%eax
  401c30:	e8 cb f1 ff ff       	callq  400e00 <__printf_chk@plt>
  401c35:	48 8b 15 24 25 20 00 	mov    0x202524(%rip),%rdx        # 604160 <user_id>
  401c3c:	be 74 32 40 00       	mov    $0x403274,%esi
  401c41:	bf 01 00 00 00       	mov    $0x1,%edi
  401c46:	b8 00 00 00 00       	mov    $0x0,%eax
  401c4b:	e8 b0 f1 ff ff       	callq  400e00 <__printf_chk@plt>
  401c50:	48 8b 15 21 25 20 00 	mov    0x202521(%rip),%rdx        # 604178 <course>
  401c57:	be 81 32 40 00       	mov    $0x403281,%esi
  401c5c:	bf 01 00 00 00       	mov    $0x1,%edi
  401c61:	b8 00 00 00 00       	mov    $0x0,%eax
  401c66:	e8 95 f1 ff ff       	callq  400e00 <__printf_chk@plt>
  401c6b:	48 8b 15 fe 24 20 00 	mov    0x2024fe(%rip),%rdx        # 604170 <lab>
  401c72:	be 8d 32 40 00       	mov    $0x40328d,%esi
  401c77:	bf 01 00 00 00       	mov    $0x1,%edi
  401c7c:	b8 00 00 00 00       	mov    $0x0,%eax
  401c81:	e8 7a f1 ff ff       	callq  400e00 <__printf_chk@plt>
  401c86:	48 89 e2             	mov    %rsp,%rdx
  401c89:	be 96 32 40 00       	mov    $0x403296,%esi
  401c8e:	bf 01 00 00 00       	mov    $0x1,%edi
  401c93:	b8 00 00 00 00       	mov    $0x0,%eax
  401c98:	e8 63 f1 ff ff       	callq  400e00 <__printf_chk@plt>
  401c9d:	48 8b 84 24 08 40 00 	mov    0x4008(%rsp),%rax
  401ca4:	00 
  401ca5:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401cac:	00 00 
  401cae:	74 05                	je     401cb5 <notify_server+0x1ea>
  401cb0:	e8 3b f0 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  401cb5:	48 81 c4 10 40 00 00 	add    $0x4010,%rsp
  401cbc:	5b                   	pop    %rbx
  401cbd:	c3                   	retq   

0000000000401cbe <validate>:
  401cbe:	53                   	push   %rbx
  401cbf:	89 fb                	mov    %edi,%ebx
  401cc1:	83 3d 60 28 20 00 00 	cmpl   $0x0,0x202860(%rip)        # 604528 <is_checker>
  401cc8:	74 6b                	je     401d35 <validate+0x77>
  401cca:	39 3d 4c 28 20 00    	cmp    %edi,0x20284c(%rip)        # 60451c <vlevel>
  401cd0:	74 14                	je     401ce6 <validate+0x28>
  401cd2:	bf a2 32 40 00       	mov    $0x4032a2,%edi
  401cd7:	e8 f4 ef ff ff       	callq  400cd0 <puts@plt>
  401cdc:	b8 00 00 00 00       	mov    $0x0,%eax
  401ce1:	e8 5e fd ff ff       	callq  401a44 <check_fail>
  401ce6:	8b 15 2c 28 20 00    	mov    0x20282c(%rip),%edx        # 604518 <check_level>
  401cec:	39 d7                	cmp    %edx,%edi
  401cee:	74 20                	je     401d10 <validate+0x52>
  401cf0:	89 f9                	mov    %edi,%ecx
  401cf2:	be e0 33 40 00       	mov    $0x4033e0,%esi
  401cf7:	bf 01 00 00 00       	mov    $0x1,%edi
  401cfc:	b8 00 00 00 00       	mov    $0x0,%eax
  401d01:	e8 fa f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401d06:	b8 00 00 00 00       	mov    $0x0,%eax
  401d0b:	e8 34 fd ff ff       	callq  401a44 <check_fail>
  401d10:	0f be 15 31 34 20 00 	movsbl 0x203431(%rip),%edx        # 605148 <target_prefix>
  401d17:	41 b8 40 45 60 00    	mov    $0x604540,%r8d
  401d1d:	89 f9                	mov    %edi,%ecx
  401d1f:	be c0 32 40 00       	mov    $0x4032c0,%esi
  401d24:	bf 01 00 00 00       	mov    $0x1,%edi
  401d29:	b8 00 00 00 00       	mov    $0x0,%eax
  401d2e:	e8 cd f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401d33:	eb 49                	jmp    401d7e <validate+0xc0>
  401d35:	3b 3d e1 27 20 00    	cmp    0x2027e1(%rip),%edi        # 60451c <vlevel>
  401d3b:	74 18                	je     401d55 <validate+0x97>
  401d3d:	bf a2 32 40 00       	mov    $0x4032a2,%edi
  401d42:	e8 89 ef ff ff       	callq  400cd0 <puts@plt>
  401d47:	89 de                	mov    %ebx,%esi
  401d49:	bf 00 00 00 00       	mov    $0x0,%edi
  401d4e:	e8 78 fd ff ff       	callq  401acb <notify_server>
  401d53:	eb 29                	jmp    401d7e <validate+0xc0>
  401d55:	0f be 0d ec 33 20 00 	movsbl 0x2033ec(%rip),%ecx        # 605148 <target_prefix>
  401d5c:	89 fa                	mov    %edi,%edx
  401d5e:	be 08 34 40 00       	mov    $0x403408,%esi
  401d63:	bf 01 00 00 00       	mov    $0x1,%edi
  401d68:	b8 00 00 00 00       	mov    $0x0,%eax
  401d6d:	e8 8e f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401d72:	89 de                	mov    %ebx,%esi
  401d74:	bf 01 00 00 00       	mov    $0x1,%edi
  401d79:	e8 4d fd ff ff       	callq  401acb <notify_server>
  401d7e:	5b                   	pop    %rbx
  401d7f:	c3                   	retq   

0000000000401d80 <fail>:
  401d80:	48 83 ec 08          	sub    $0x8,%rsp
  401d84:	83 3d 9d 27 20 00 00 	cmpl   $0x0,0x20279d(%rip)        # 604528 <is_checker>
  401d8b:	74 0a                	je     401d97 <fail+0x17>
  401d8d:	b8 00 00 00 00       	mov    $0x0,%eax
  401d92:	e8 ad fc ff ff       	callq  401a44 <check_fail>
  401d97:	89 fe                	mov    %edi,%esi
  401d99:	bf 00 00 00 00       	mov    $0x0,%edi
  401d9e:	e8 28 fd ff ff       	callq  401acb <notify_server>
  401da3:	48 83 c4 08          	add    $0x8,%rsp
  401da7:	c3                   	retq   

0000000000401da8 <bushandler>:
  401da8:	48 83 ec 08          	sub    $0x8,%rsp
  401dac:	83 3d 75 27 20 00 00 	cmpl   $0x0,0x202775(%rip)        # 604528 <is_checker>
  401db3:	74 14                	je     401dc9 <bushandler+0x21>
  401db5:	bf d5 32 40 00       	mov    $0x4032d5,%edi
  401dba:	e8 11 ef ff ff       	callq  400cd0 <puts@plt>
  401dbf:	b8 00 00 00 00       	mov    $0x0,%eax
  401dc4:	e8 7b fc ff ff       	callq  401a44 <check_fail>
  401dc9:	bf 40 34 40 00       	mov    $0x403440,%edi
  401dce:	e8 fd ee ff ff       	callq  400cd0 <puts@plt>
  401dd3:	bf df 32 40 00       	mov    $0x4032df,%edi
  401dd8:	e8 f3 ee ff ff       	callq  400cd0 <puts@plt>
  401ddd:	be 00 00 00 00       	mov    $0x0,%esi
  401de2:	bf 00 00 00 00       	mov    $0x0,%edi
  401de7:	e8 df fc ff ff       	callq  401acb <notify_server>
  401dec:	bf 01 00 00 00       	mov    $0x1,%edi
  401df1:	e8 5a f0 ff ff       	callq  400e50 <exit@plt>

0000000000401df6 <seghandler>:
  401df6:	48 83 ec 08          	sub    $0x8,%rsp
  401dfa:	83 3d 27 27 20 00 00 	cmpl   $0x0,0x202727(%rip)        # 604528 <is_checker>
  401e01:	74 14                	je     401e17 <seghandler+0x21>
  401e03:	bf f5 32 40 00       	mov    $0x4032f5,%edi
  401e08:	e8 c3 ee ff ff       	callq  400cd0 <puts@plt>
  401e0d:	b8 00 00 00 00       	mov    $0x0,%eax
  401e12:	e8 2d fc ff ff       	callq  401a44 <check_fail>
  401e17:	bf 60 34 40 00       	mov    $0x403460,%edi
  401e1c:	e8 af ee ff ff       	callq  400cd0 <puts@plt>
  401e21:	bf df 32 40 00       	mov    $0x4032df,%edi
  401e26:	e8 a5 ee ff ff       	callq  400cd0 <puts@plt>
  401e2b:	be 00 00 00 00       	mov    $0x0,%esi
  401e30:	bf 00 00 00 00       	mov    $0x0,%edi
  401e35:	e8 91 fc ff ff       	callq  401acb <notify_server>
  401e3a:	bf 01 00 00 00       	mov    $0x1,%edi
  401e3f:	e8 0c f0 ff ff       	callq  400e50 <exit@plt>

0000000000401e44 <illegalhandler>:
  401e44:	48 83 ec 08          	sub    $0x8,%rsp
  401e48:	83 3d d9 26 20 00 00 	cmpl   $0x0,0x2026d9(%rip)        # 604528 <is_checker>
  401e4f:	74 14                	je     401e65 <illegalhandler+0x21>
  401e51:	bf 08 33 40 00       	mov    $0x403308,%edi
  401e56:	e8 75 ee ff ff       	callq  400cd0 <puts@plt>
  401e5b:	b8 00 00 00 00       	mov    $0x0,%eax
  401e60:	e8 df fb ff ff       	callq  401a44 <check_fail>
  401e65:	bf 88 34 40 00       	mov    $0x403488,%edi
  401e6a:	e8 61 ee ff ff       	callq  400cd0 <puts@plt>
  401e6f:	bf df 32 40 00       	mov    $0x4032df,%edi
  401e74:	e8 57 ee ff ff       	callq  400cd0 <puts@plt>
  401e79:	be 00 00 00 00       	mov    $0x0,%esi
  401e7e:	bf 00 00 00 00       	mov    $0x0,%edi
  401e83:	e8 43 fc ff ff       	callq  401acb <notify_server>
  401e88:	bf 01 00 00 00       	mov    $0x1,%edi
  401e8d:	e8 be ef ff ff       	callq  400e50 <exit@plt>

0000000000401e92 <sigalrmhandler>:
  401e92:	48 83 ec 08          	sub    $0x8,%rsp
  401e96:	83 3d 8b 26 20 00 00 	cmpl   $0x0,0x20268b(%rip)        # 604528 <is_checker>
  401e9d:	74 14                	je     401eb3 <sigalrmhandler+0x21>
  401e9f:	bf 1c 33 40 00       	mov    $0x40331c,%edi
  401ea4:	e8 27 ee ff ff       	callq  400cd0 <puts@plt>
  401ea9:	b8 00 00 00 00       	mov    $0x0,%eax
  401eae:	e8 91 fb ff ff       	callq  401a44 <check_fail>
  401eb3:	ba 05 00 00 00       	mov    $0x5,%edx
  401eb8:	be b8 34 40 00       	mov    $0x4034b8,%esi
  401ebd:	bf 01 00 00 00       	mov    $0x1,%edi
  401ec2:	b8 00 00 00 00       	mov    $0x0,%eax
  401ec7:	e8 34 ef ff ff       	callq  400e00 <__printf_chk@plt>
  401ecc:	be 00 00 00 00       	mov    $0x0,%esi
  401ed1:	bf 00 00 00 00       	mov    $0x0,%edi
  401ed6:	e8 f0 fb ff ff       	callq  401acb <notify_server>
  401edb:	bf 01 00 00 00       	mov    $0x1,%edi
  401ee0:	e8 6b ef ff ff       	callq  400e50 <exit@plt>

0000000000401ee5 <launch>:
  401ee5:	55                   	push   %rbp
  401ee6:	48 89 e5             	mov    %rsp,%rbp
  401ee9:	48 83 ec 10          	sub    $0x10,%rsp
  401eed:	48 89 fa             	mov    %rdi,%rdx
  401ef0:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401ef7:	00 00 
  401ef9:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  401efd:	31 c0                	xor    %eax,%eax
  401eff:	48 8d 47 1e          	lea    0x1e(%rdi),%rax
  401f03:	48 83 e0 f0          	and    $0xfffffffffffffff0,%rax
  401f07:	48 29 c4             	sub    %rax,%rsp
  401f0a:	48 8d 7c 24 0f       	lea    0xf(%rsp),%rdi
  401f0f:	48 83 e7 f0          	and    $0xfffffffffffffff0,%rdi
  401f13:	be f4 00 00 00       	mov    $0xf4,%esi
  401f18:	e8 f3 ed ff ff       	callq  400d10 <memset@plt>
  401f1d:	48 8b 05 9c 25 20 00 	mov    0x20259c(%rip),%rax        # 6044c0 <stdin@@GLIBC_2.2.5>
  401f24:	48 39 05 e5 25 20 00 	cmp    %rax,0x2025e5(%rip)        # 604510 <infile>
  401f2b:	75 14                	jne    401f41 <launch+0x5c>
  401f2d:	be 24 33 40 00       	mov    $0x403324,%esi
  401f32:	bf 01 00 00 00       	mov    $0x1,%edi
  401f37:	b8 00 00 00 00       	mov    $0x0,%eax
  401f3c:	e8 bf ee ff ff       	callq  400e00 <__printf_chk@plt>
  401f41:	c7 05 d1 25 20 00 00 	movl   $0x0,0x2025d1(%rip)        # 60451c <vlevel>
  401f48:	00 00 00 
  401f4b:	b8 00 00 00 00       	mov    $0x0,%eax
  401f50:	e8 5b fa ff ff       	callq  4019b0 <test>
  401f55:	83 3d cc 25 20 00 00 	cmpl   $0x0,0x2025cc(%rip)        # 604528 <is_checker>
  401f5c:	74 14                	je     401f72 <launch+0x8d>
  401f5e:	bf 31 33 40 00       	mov    $0x403331,%edi
  401f63:	e8 68 ed ff ff       	callq  400cd0 <puts@plt>
  401f68:	b8 00 00 00 00       	mov    $0x0,%eax
  401f6d:	e8 d2 fa ff ff       	callq  401a44 <check_fail>
  401f72:	bf 3c 33 40 00       	mov    $0x40333c,%edi
  401f77:	e8 54 ed ff ff       	callq  400cd0 <puts@plt>
  401f7c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401f80:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401f87:	00 00 
  401f89:	74 05                	je     401f90 <launch+0xab>
  401f8b:	e8 60 ed ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  401f90:	c9                   	leaveq 
  401f91:	c3                   	retq   

0000000000401f92 <stable_launch>:
  401f92:	53                   	push   %rbx
  401f93:	48 89 3d 6e 25 20 00 	mov    %rdi,0x20256e(%rip)        # 604508 <global_offset>
  401f9a:	41 b9 00 00 00 00    	mov    $0x0,%r9d
  401fa0:	41 b8 00 00 00 00    	mov    $0x0,%r8d
  401fa6:	b9 32 01 00 00       	mov    $0x132,%ecx
  401fab:	ba 07 00 00 00       	mov    $0x7,%edx
  401fb0:	be 00 00 10 00       	mov    $0x100000,%esi
  401fb5:	bf 00 60 58 55       	mov    $0x55586000,%edi
  401fba:	e8 41 ed ff ff       	callq  400d00 <mmap@plt>
  401fbf:	48 89 c3             	mov    %rax,%rbx
  401fc2:	48 3d 00 60 58 55    	cmp    $0x55586000,%rax
  401fc8:	74 37                	je     402001 <stable_launch+0x6f>
  401fca:	be 00 00 10 00       	mov    $0x100000,%esi
  401fcf:	48 89 c7             	mov    %rax,%rdi
  401fd2:	e8 19 ee ff ff       	callq  400df0 <munmap@plt>
  401fd7:	b9 00 60 58 55       	mov    $0x55586000,%ecx
  401fdc:	ba f0 34 40 00       	mov    $0x4034f0,%edx
  401fe1:	be 01 00 00 00       	mov    $0x1,%esi
  401fe6:	48 8b 3d f3 24 20 00 	mov    0x2024f3(%rip),%rdi        # 6044e0 <stderr@@GLIBC_2.2.5>
  401fed:	b8 00 00 00 00       	mov    $0x0,%eax
  401ff2:	e8 79 ee ff ff       	callq  400e70 <__fprintf_chk@plt>
  401ff7:	bf 01 00 00 00       	mov    $0x1,%edi
  401ffc:	e8 4f ee ff ff       	callq  400e50 <exit@plt>
  402001:	48 8d 90 f8 ff 0f 00 	lea    0xffff8(%rax),%rdx
  402008:	48 89 15 41 31 20 00 	mov    %rdx,0x203141(%rip)        # 605150 <stack_top>
  40200f:	48 89 e0             	mov    %rsp,%rax
  402012:	48 89 d4             	mov    %rdx,%rsp
  402015:	48 89 c2             	mov    %rax,%rdx
  402018:	48 89 15 e1 24 20 00 	mov    %rdx,0x2024e1(%rip)        # 604500 <global_save_stack>
  40201f:	48 8b 3d e2 24 20 00 	mov    0x2024e2(%rip),%rdi        # 604508 <global_offset>
  402026:	e8 ba fe ff ff       	callq  401ee5 <launch>
  40202b:	48 8b 05 ce 24 20 00 	mov    0x2024ce(%rip),%rax        # 604500 <global_save_stack>
  402032:	48 89 c4             	mov    %rax,%rsp
  402035:	be 00 00 10 00       	mov    $0x100000,%esi
  40203a:	48 89 df             	mov    %rbx,%rdi
  40203d:	e8 ae ed ff ff       	callq  400df0 <munmap@plt>
  402042:	5b                   	pop    %rbx
  402043:	c3                   	retq   

0000000000402044 <rio_readinitb>:
  402044:	89 37                	mov    %esi,(%rdi)
  402046:	c7 47 04 00 00 00 00 	movl   $0x0,0x4(%rdi)
  40204d:	48 8d 47 10          	lea    0x10(%rdi),%rax
  402051:	48 89 47 08          	mov    %rax,0x8(%rdi)
  402055:	c3                   	retq   

0000000000402056 <sigalrm_handler>:
  402056:	48 83 ec 08          	sub    $0x8,%rsp
  40205a:	b9 00 00 00 00       	mov    $0x0,%ecx
  40205f:	ba 30 35 40 00       	mov    $0x403530,%edx
  402064:	be 01 00 00 00       	mov    $0x1,%esi
  402069:	48 8b 3d 70 24 20 00 	mov    0x202470(%rip),%rdi        # 6044e0 <stderr@@GLIBC_2.2.5>
  402070:	b8 00 00 00 00       	mov    $0x0,%eax
  402075:	e8 f6 ed ff ff       	callq  400e70 <__fprintf_chk@plt>
  40207a:	bf 01 00 00 00       	mov    $0x1,%edi
  40207f:	e8 cc ed ff ff       	callq  400e50 <exit@plt>

0000000000402084 <rio_writen>:
  402084:	41 55                	push   %r13
  402086:	41 54                	push   %r12
  402088:	55                   	push   %rbp
  402089:	53                   	push   %rbx
  40208a:	48 83 ec 08          	sub    $0x8,%rsp
  40208e:	41 89 fc             	mov    %edi,%r12d
  402091:	48 89 f5             	mov    %rsi,%rbp
  402094:	49 89 d5             	mov    %rdx,%r13
  402097:	48 89 d3             	mov    %rdx,%rbx
  40209a:	eb 28                	jmp    4020c4 <rio_writen+0x40>
  40209c:	48 89 da             	mov    %rbx,%rdx
  40209f:	48 89 ee             	mov    %rbp,%rsi
  4020a2:	44 89 e7             	mov    %r12d,%edi
  4020a5:	e8 36 ec ff ff       	callq  400ce0 <write@plt>
  4020aa:	48 85 c0             	test   %rax,%rax
  4020ad:	7f 0f                	jg     4020be <rio_writen+0x3a>
  4020af:	e8 dc eb ff ff       	callq  400c90 <__errno_location@plt>
  4020b4:	83 38 04             	cmpl   $0x4,(%rax)
  4020b7:	75 15                	jne    4020ce <rio_writen+0x4a>
  4020b9:	b8 00 00 00 00       	mov    $0x0,%eax
  4020be:	48 29 c3             	sub    %rax,%rbx
  4020c1:	48 01 c5             	add    %rax,%rbp
  4020c4:	48 85 db             	test   %rbx,%rbx
  4020c7:	75 d3                	jne    40209c <rio_writen+0x18>
  4020c9:	4c 89 e8             	mov    %r13,%rax
  4020cc:	eb 07                	jmp    4020d5 <rio_writen+0x51>
  4020ce:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  4020d5:	48 83 c4 08          	add    $0x8,%rsp
  4020d9:	5b                   	pop    %rbx
  4020da:	5d                   	pop    %rbp
  4020db:	41 5c                	pop    %r12
  4020dd:	41 5d                	pop    %r13
  4020df:	c3                   	retq   

00000000004020e0 <rio_read>:
  4020e0:	41 55                	push   %r13
  4020e2:	41 54                	push   %r12
  4020e4:	55                   	push   %rbp
  4020e5:	53                   	push   %rbx
  4020e6:	48 83 ec 08          	sub    $0x8,%rsp
  4020ea:	48 89 fb             	mov    %rdi,%rbx
  4020ed:	49 89 f5             	mov    %rsi,%r13
  4020f0:	49 89 d4             	mov    %rdx,%r12
  4020f3:	eb 2e                	jmp    402123 <rio_read+0x43>
  4020f5:	48 8d 6b 10          	lea    0x10(%rbx),%rbp
  4020f9:	8b 3b                	mov    (%rbx),%edi
  4020fb:	ba 00 20 00 00       	mov    $0x2000,%edx
  402100:	48 89 ee             	mov    %rbp,%rsi
  402103:	e8 38 ec ff ff       	callq  400d40 <read@plt>
  402108:	89 43 04             	mov    %eax,0x4(%rbx)
  40210b:	85 c0                	test   %eax,%eax
  40210d:	79 0c                	jns    40211b <rio_read+0x3b>
  40210f:	e8 7c eb ff ff       	callq  400c90 <__errno_location@plt>
  402114:	83 38 04             	cmpl   $0x4,(%rax)
  402117:	74 0a                	je     402123 <rio_read+0x43>
  402119:	eb 37                	jmp    402152 <rio_read+0x72>
  40211b:	85 c0                	test   %eax,%eax
  40211d:	74 3c                	je     40215b <rio_read+0x7b>
  40211f:	48 89 6b 08          	mov    %rbp,0x8(%rbx)
  402123:	8b 6b 04             	mov    0x4(%rbx),%ebp
  402126:	85 ed                	test   %ebp,%ebp
  402128:	7e cb                	jle    4020f5 <rio_read+0x15>
  40212a:	89 e8                	mov    %ebp,%eax
  40212c:	49 39 c4             	cmp    %rax,%r12
  40212f:	77 03                	ja     402134 <rio_read+0x54>
  402131:	44 89 e5             	mov    %r12d,%ebp
  402134:	4c 63 e5             	movslq %ebp,%r12
  402137:	48 8b 73 08          	mov    0x8(%rbx),%rsi
  40213b:	4c 89 e2             	mov    %r12,%rdx
  40213e:	4c 89 ef             	mov    %r13,%rdi
  402141:	e8 5a ec ff ff       	callq  400da0 <memcpy@plt>
  402146:	4c 01 63 08          	add    %r12,0x8(%rbx)
  40214a:	29 6b 04             	sub    %ebp,0x4(%rbx)
  40214d:	4c 89 e0             	mov    %r12,%rax
  402150:	eb 0e                	jmp    402160 <rio_read+0x80>
  402152:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  402159:	eb 05                	jmp    402160 <rio_read+0x80>
  40215b:	b8 00 00 00 00       	mov    $0x0,%eax
  402160:	48 83 c4 08          	add    $0x8,%rsp
  402164:	5b                   	pop    %rbx
  402165:	5d                   	pop    %rbp
  402166:	41 5c                	pop    %r12
  402168:	41 5d                	pop    %r13
  40216a:	c3                   	retq   

000000000040216b <rio_readlineb>:
  40216b:	41 55                	push   %r13
  40216d:	41 54                	push   %r12
  40216f:	55                   	push   %rbp
  402170:	53                   	push   %rbx
  402171:	48 83 ec 18          	sub    $0x18,%rsp
  402175:	49 89 fd             	mov    %rdi,%r13
  402178:	48 89 f5             	mov    %rsi,%rbp
  40217b:	49 89 d4             	mov    %rdx,%r12
  40217e:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  402185:	00 00 
  402187:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  40218c:	31 c0                	xor    %eax,%eax
  40218e:	bb 01 00 00 00       	mov    $0x1,%ebx
  402193:	eb 3f                	jmp    4021d4 <rio_readlineb+0x69>
  402195:	ba 01 00 00 00       	mov    $0x1,%edx
  40219a:	48 8d 74 24 07       	lea    0x7(%rsp),%rsi
  40219f:	4c 89 ef             	mov    %r13,%rdi
  4021a2:	e8 39 ff ff ff       	callq  4020e0 <rio_read>
  4021a7:	83 f8 01             	cmp    $0x1,%eax
  4021aa:	75 15                	jne    4021c1 <rio_readlineb+0x56>
  4021ac:	48 8d 45 01          	lea    0x1(%rbp),%rax
  4021b0:	0f b6 54 24 07       	movzbl 0x7(%rsp),%edx
  4021b5:	88 55 00             	mov    %dl,0x0(%rbp)
  4021b8:	80 7c 24 07 0a       	cmpb   $0xa,0x7(%rsp)
  4021bd:	75 0e                	jne    4021cd <rio_readlineb+0x62>
  4021bf:	eb 1a                	jmp    4021db <rio_readlineb+0x70>
  4021c1:	85 c0                	test   %eax,%eax
  4021c3:	75 22                	jne    4021e7 <rio_readlineb+0x7c>
  4021c5:	48 83 fb 01          	cmp    $0x1,%rbx
  4021c9:	75 13                	jne    4021de <rio_readlineb+0x73>
  4021cb:	eb 23                	jmp    4021f0 <rio_readlineb+0x85>
  4021cd:	48 83 c3 01          	add    $0x1,%rbx
  4021d1:	48 89 c5             	mov    %rax,%rbp
  4021d4:	4c 39 e3             	cmp    %r12,%rbx
  4021d7:	72 bc                	jb     402195 <rio_readlineb+0x2a>
  4021d9:	eb 03                	jmp    4021de <rio_readlineb+0x73>
  4021db:	48 89 c5             	mov    %rax,%rbp
  4021de:	c6 45 00 00          	movb   $0x0,0x0(%rbp)
  4021e2:	48 89 d8             	mov    %rbx,%rax
  4021e5:	eb 0e                	jmp    4021f5 <rio_readlineb+0x8a>
  4021e7:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  4021ee:	eb 05                	jmp    4021f5 <rio_readlineb+0x8a>
  4021f0:	b8 00 00 00 00       	mov    $0x0,%eax
  4021f5:	48 8b 4c 24 08       	mov    0x8(%rsp),%rcx
  4021fa:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  402201:	00 00 
  402203:	74 05                	je     40220a <rio_readlineb+0x9f>
  402205:	e8 e6 ea ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  40220a:	48 83 c4 18          	add    $0x18,%rsp
  40220e:	5b                   	pop    %rbx
  40220f:	5d                   	pop    %rbp
  402210:	41 5c                	pop    %r12
  402212:	41 5d                	pop    %r13
  402214:	c3                   	retq   

0000000000402215 <urlencode>:
  402215:	41 54                	push   %r12
  402217:	55                   	push   %rbp
  402218:	53                   	push   %rbx
  402219:	48 83 ec 10          	sub    $0x10,%rsp
  40221d:	48 89 fb             	mov    %rdi,%rbx
  402220:	48 89 f5             	mov    %rsi,%rbp
  402223:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40222a:	00 00 
  40222c:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  402231:	31 c0                	xor    %eax,%eax
  402233:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  40223a:	f2 ae                	repnz scas %es:(%rdi),%al
  40223c:	48 f7 d1             	not    %rcx
  40223f:	8d 41 ff             	lea    -0x1(%rcx),%eax
  402242:	e9 aa 00 00 00       	jmpq   4022f1 <urlencode+0xdc>
  402247:	44 0f b6 03          	movzbl (%rbx),%r8d
  40224b:	41 80 f8 2a          	cmp    $0x2a,%r8b
  40224f:	0f 94 c2             	sete   %dl
  402252:	41 80 f8 2d          	cmp    $0x2d,%r8b
  402256:	0f 94 c0             	sete   %al
  402259:	08 c2                	or     %al,%dl
  40225b:	75 24                	jne    402281 <urlencode+0x6c>
  40225d:	41 80 f8 2e          	cmp    $0x2e,%r8b
  402261:	74 1e                	je     402281 <urlencode+0x6c>
  402263:	41 80 f8 5f          	cmp    $0x5f,%r8b
  402267:	74 18                	je     402281 <urlencode+0x6c>
  402269:	41 8d 40 d0          	lea    -0x30(%r8),%eax
  40226d:	3c 09                	cmp    $0x9,%al
  40226f:	76 10                	jbe    402281 <urlencode+0x6c>
  402271:	41 8d 40 bf          	lea    -0x41(%r8),%eax
  402275:	3c 19                	cmp    $0x19,%al
  402277:	76 08                	jbe    402281 <urlencode+0x6c>
  402279:	41 8d 40 9f          	lea    -0x61(%r8),%eax
  40227d:	3c 19                	cmp    $0x19,%al
  40227f:	77 0a                	ja     40228b <urlencode+0x76>
  402281:	44 88 45 00          	mov    %r8b,0x0(%rbp)
  402285:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  402289:	eb 5f                	jmp    4022ea <urlencode+0xd5>
  40228b:	41 80 f8 20          	cmp    $0x20,%r8b
  40228f:	75 0a                	jne    40229b <urlencode+0x86>
  402291:	c6 45 00 2b          	movb   $0x2b,0x0(%rbp)
  402295:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  402299:	eb 4f                	jmp    4022ea <urlencode+0xd5>
  40229b:	41 8d 40 e0          	lea    -0x20(%r8),%eax
  40229f:	3c 5f                	cmp    $0x5f,%al
  4022a1:	0f 96 c2             	setbe  %dl
  4022a4:	41 80 f8 09          	cmp    $0x9,%r8b
  4022a8:	0f 94 c0             	sete   %al
  4022ab:	08 c2                	or     %al,%dl
  4022ad:	74 50                	je     4022ff <urlencode+0xea>
  4022af:	45 0f b6 c0          	movzbl %r8b,%r8d
  4022b3:	b9 c8 35 40 00       	mov    $0x4035c8,%ecx
  4022b8:	ba 08 00 00 00       	mov    $0x8,%edx
  4022bd:	be 01 00 00 00       	mov    $0x1,%esi
  4022c2:	48 89 e7             	mov    %rsp,%rdi
  4022c5:	b8 00 00 00 00       	mov    $0x0,%eax
  4022ca:	e8 b1 eb ff ff       	callq  400e80 <__sprintf_chk@plt>
  4022cf:	0f b6 04 24          	movzbl (%rsp),%eax
  4022d3:	88 45 00             	mov    %al,0x0(%rbp)
  4022d6:	0f b6 44 24 01       	movzbl 0x1(%rsp),%eax
  4022db:	88 45 01             	mov    %al,0x1(%rbp)
  4022de:	0f b6 44 24 02       	movzbl 0x2(%rsp),%eax
  4022e3:	88 45 02             	mov    %al,0x2(%rbp)
  4022e6:	48 8d 6d 03          	lea    0x3(%rbp),%rbp
  4022ea:	48 83 c3 01          	add    $0x1,%rbx
  4022ee:	44 89 e0             	mov    %r12d,%eax
  4022f1:	44 8d 60 ff          	lea    -0x1(%rax),%r12d
  4022f5:	85 c0                	test   %eax,%eax
  4022f7:	0f 85 4a ff ff ff    	jne    402247 <urlencode+0x32>
  4022fd:	eb 05                	jmp    402304 <urlencode+0xef>
  4022ff:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402304:	48 8b 74 24 08       	mov    0x8(%rsp),%rsi
  402309:	64 48 33 34 25 28 00 	xor    %fs:0x28,%rsi
  402310:	00 00 
  402312:	74 05                	je     402319 <urlencode+0x104>
  402314:	e8 d7 e9 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  402319:	48 83 c4 10          	add    $0x10,%rsp
  40231d:	5b                   	pop    %rbx
  40231e:	5d                   	pop    %rbp
  40231f:	41 5c                	pop    %r12
  402321:	c3                   	retq   

0000000000402322 <submitr>:
  402322:	41 57                	push   %r15
  402324:	41 56                	push   %r14
  402326:	41 55                	push   %r13
  402328:	41 54                	push   %r12
  40232a:	55                   	push   %rbp
  40232b:	53                   	push   %rbx
  40232c:	48 81 ec 58 a0 00 00 	sub    $0xa058,%rsp
  402333:	49 89 fc             	mov    %rdi,%r12
  402336:	89 74 24 04          	mov    %esi,0x4(%rsp)
  40233a:	49 89 d7             	mov    %rdx,%r15
  40233d:	49 89 ce             	mov    %rcx,%r14
  402340:	4c 89 44 24 08       	mov    %r8,0x8(%rsp)
  402345:	4d 89 cd             	mov    %r9,%r13
  402348:	48 8b 9c 24 90 a0 00 	mov    0xa090(%rsp),%rbx
  40234f:	00 
  402350:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  402357:	00 00 
  402359:	48 89 84 24 48 a0 00 	mov    %rax,0xa048(%rsp)
  402360:	00 
  402361:	31 c0                	xor    %eax,%eax
  402363:	c7 44 24 1c 00 00 00 	movl   $0x0,0x1c(%rsp)
  40236a:	00 
  40236b:	ba 00 00 00 00       	mov    $0x0,%edx
  402370:	be 01 00 00 00       	mov    $0x1,%esi
  402375:	bf 02 00 00 00       	mov    $0x2,%edi
  40237a:	e8 11 eb ff ff       	callq  400e90 <socket@plt>
  40237f:	85 c0                	test   %eax,%eax
  402381:	79 4e                	jns    4023d1 <submitr+0xaf>
  402383:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  40238a:	3a 20 43 
  40238d:	48 89 03             	mov    %rax,(%rbx)
  402390:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402397:	20 75 6e 
  40239a:	48 89 43 08          	mov    %rax,0x8(%rbx)
  40239e:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4023a5:	74 6f 20 
  4023a8:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4023ac:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  4023b3:	65 20 73 
  4023b6:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4023ba:	c7 43 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbx)
  4023c1:	66 c7 43 24 74 00    	movw   $0x74,0x24(%rbx)
  4023c7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4023cc:	e9 97 06 00 00       	jmpq   402a68 <submitr+0x746>
  4023d1:	89 c5                	mov    %eax,%ebp
  4023d3:	4c 89 e7             	mov    %r12,%rdi
  4023d6:	e8 95 e9 ff ff       	callq  400d70 <gethostbyname@plt>
  4023db:	48 85 c0             	test   %rax,%rax
  4023de:	75 67                	jne    402447 <submitr+0x125>
  4023e0:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  4023e7:	3a 20 44 
  4023ea:	48 89 03             	mov    %rax,(%rbx)
  4023ed:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  4023f4:	20 75 6e 
  4023f7:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4023fb:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402402:	74 6f 20 
  402405:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402409:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  402410:	76 65 20 
  402413:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402417:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  40241e:	72 20 61 
  402421:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402425:	c7 43 28 64 64 72 65 	movl   $0x65726464,0x28(%rbx)
  40242c:	66 c7 43 2c 73 73    	movw   $0x7373,0x2c(%rbx)
  402432:	c6 43 2e 00          	movb   $0x0,0x2e(%rbx)
  402436:	89 ef                	mov    %ebp,%edi
  402438:	e8 f3 e8 ff ff       	callq  400d30 <close@plt>
  40243d:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402442:	e9 21 06 00 00       	jmpq   402a68 <submitr+0x746>
  402447:	48 c7 44 24 20 00 00 	movq   $0x0,0x20(%rsp)
  40244e:	00 00 
  402450:	48 c7 44 24 28 00 00 	movq   $0x0,0x28(%rsp)
  402457:	00 00 
  402459:	66 c7 44 24 20 02 00 	movw   $0x2,0x20(%rsp)
  402460:	48 63 50 14          	movslq 0x14(%rax),%rdx
  402464:	48 8b 40 18          	mov    0x18(%rax),%rax
  402468:	48 8b 30             	mov    (%rax),%rsi
  40246b:	48 8d 7c 24 24       	lea    0x24(%rsp),%rdi
  402470:	b9 0c 00 00 00       	mov    $0xc,%ecx
  402475:	e8 06 e9 ff ff       	callq  400d80 <__memmove_chk@plt>
  40247a:	0f b7 44 24 04       	movzwl 0x4(%rsp),%eax
  40247f:	66 c1 c8 08          	ror    $0x8,%ax
  402483:	66 89 44 24 22       	mov    %ax,0x22(%rsp)
  402488:	ba 10 00 00 00       	mov    $0x10,%edx
  40248d:	48 8d 74 24 20       	lea    0x20(%rsp),%rsi
  402492:	89 ef                	mov    %ebp,%edi
  402494:	e8 c7 e9 ff ff       	callq  400e60 <connect@plt>
  402499:	85 c0                	test   %eax,%eax
  40249b:	79 59                	jns    4024f6 <submitr+0x1d4>
  40249d:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  4024a4:	3a 20 55 
  4024a7:	48 89 03             	mov    %rax,(%rbx)
  4024aa:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  4024b1:	20 74 6f 
  4024b4:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4024b8:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  4024bf:	65 63 74 
  4024c2:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4024c6:	48 b8 20 74 6f 20 74 	movabs $0x20656874206f7420,%rax
  4024cd:	68 65 20 
  4024d0:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4024d4:	c7 43 20 73 65 72 76 	movl   $0x76726573,0x20(%rbx)
  4024db:	66 c7 43 24 65 72    	movw   $0x7265,0x24(%rbx)
  4024e1:	c6 43 26 00          	movb   $0x0,0x26(%rbx)
  4024e5:	89 ef                	mov    %ebp,%edi
  4024e7:	e8 44 e8 ff ff       	callq  400d30 <close@plt>
  4024ec:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4024f1:	e9 72 05 00 00       	jmpq   402a68 <submitr+0x746>
  4024f6:	48 c7 c6 ff ff ff ff 	mov    $0xffffffffffffffff,%rsi
  4024fd:	b8 00 00 00 00       	mov    $0x0,%eax
  402502:	48 89 f1             	mov    %rsi,%rcx
  402505:	4c 89 ef             	mov    %r13,%rdi
  402508:	f2 ae                	repnz scas %es:(%rdi),%al
  40250a:	48 f7 d1             	not    %rcx
  40250d:	48 89 ca             	mov    %rcx,%rdx
  402510:	48 89 f1             	mov    %rsi,%rcx
  402513:	4c 89 ff             	mov    %r15,%rdi
  402516:	f2 ae                	repnz scas %es:(%rdi),%al
  402518:	48 f7 d1             	not    %rcx
  40251b:	49 89 c8             	mov    %rcx,%r8
  40251e:	48 89 f1             	mov    %rsi,%rcx
  402521:	4c 89 f7             	mov    %r14,%rdi
  402524:	f2 ae                	repnz scas %es:(%rdi),%al
  402526:	48 f7 d1             	not    %rcx
  402529:	4d 8d 44 08 fe       	lea    -0x2(%r8,%rcx,1),%r8
  40252e:	48 89 f1             	mov    %rsi,%rcx
  402531:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  402536:	f2 ae                	repnz scas %es:(%rdi),%al
  402538:	48 89 c8             	mov    %rcx,%rax
  40253b:	48 f7 d0             	not    %rax
  40253e:	49 8d 4c 00 ff       	lea    -0x1(%r8,%rax,1),%rcx
  402543:	48 8d 44 52 fd       	lea    -0x3(%rdx,%rdx,2),%rax
  402548:	48 8d 84 01 80 00 00 	lea    0x80(%rcx,%rax,1),%rax
  40254f:	00 
  402550:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
  402556:	76 72                	jbe    4025ca <submitr+0x2a8>
  402558:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  40255f:	3a 20 52 
  402562:	48 89 03             	mov    %rax,(%rbx)
  402565:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  40256c:	20 73 74 
  40256f:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402573:	48 b8 72 69 6e 67 20 	movabs $0x6f6f7420676e6972,%rax
  40257a:	74 6f 6f 
  40257d:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402581:	48 b8 20 6c 61 72 67 	movabs $0x202e656772616c20,%rax
  402588:	65 2e 20 
  40258b:	48 89 43 18          	mov    %rax,0x18(%rbx)
  40258f:	48 b8 49 6e 63 72 65 	movabs $0x6573616572636e49,%rax
  402596:	61 73 65 
  402599:	48 89 43 20          	mov    %rax,0x20(%rbx)
  40259d:	48 b8 20 53 55 42 4d 	movabs $0x5254494d42555320,%rax
  4025a4:	49 54 52 
  4025a7:	48 89 43 28          	mov    %rax,0x28(%rbx)
  4025ab:	48 b8 5f 4d 41 58 42 	movabs $0x46554258414d5f,%rax
  4025b2:	55 46 00 
  4025b5:	48 89 43 30          	mov    %rax,0x30(%rbx)
  4025b9:	89 ef                	mov    %ebp,%edi
  4025bb:	e8 70 e7 ff ff       	callq  400d30 <close@plt>
  4025c0:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4025c5:	e9 9e 04 00 00       	jmpq   402a68 <submitr+0x746>
  4025ca:	48 8d b4 24 40 40 00 	lea    0x4040(%rsp),%rsi
  4025d1:	00 
  4025d2:	b9 00 04 00 00       	mov    $0x400,%ecx
  4025d7:	b8 00 00 00 00       	mov    $0x0,%eax
  4025dc:	48 89 f7             	mov    %rsi,%rdi
  4025df:	f3 48 ab             	rep stos %rax,%es:(%rdi)
  4025e2:	4c 89 ef             	mov    %r13,%rdi
  4025e5:	e8 2b fc ff ff       	callq  402215 <urlencode>
  4025ea:	85 c0                	test   %eax,%eax
  4025ec:	0f 89 8a 00 00 00    	jns    40267c <submitr+0x35a>
  4025f2:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  4025f9:	3a 20 52 
  4025fc:	48 89 03             	mov    %rax,(%rbx)
  4025ff:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  402606:	20 73 74 
  402609:	48 89 43 08          	mov    %rax,0x8(%rbx)
  40260d:	48 b8 72 69 6e 67 20 	movabs $0x6e6f6320676e6972,%rax
  402614:	63 6f 6e 
  402617:	48 89 43 10          	mov    %rax,0x10(%rbx)
  40261b:	48 b8 74 61 69 6e 73 	movabs $0x6e6120736e696174,%rax
  402622:	20 61 6e 
  402625:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402629:	48 b8 20 69 6c 6c 65 	movabs $0x6c6167656c6c6920,%rax
  402630:	67 61 6c 
  402633:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402637:	48 b8 20 6f 72 20 75 	movabs $0x72706e7520726f20,%rax
  40263e:	6e 70 72 
  402641:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402645:	48 b8 69 6e 74 61 62 	movabs $0x20656c6261746e69,%rax
  40264c:	6c 65 20 
  40264f:	48 89 43 30          	mov    %rax,0x30(%rbx)
  402653:	48 b8 63 68 61 72 61 	movabs $0x6574636172616863,%rax
  40265a:	63 74 65 
  40265d:	48 89 43 38          	mov    %rax,0x38(%rbx)
  402661:	66 c7 43 40 72 2e    	movw   $0x2e72,0x40(%rbx)
  402667:	c6 43 42 00          	movb   $0x0,0x42(%rbx)
  40266b:	89 ef                	mov    %ebp,%edi
  40266d:	e8 be e6 ff ff       	callq  400d30 <close@plt>
  402672:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402677:	e9 ec 03 00 00       	jmpq   402a68 <submitr+0x746>
  40267c:	4c 8d ac 24 40 20 00 	lea    0x2040(%rsp),%r13
  402683:	00 
  402684:	41 54                	push   %r12
  402686:	48 8d 84 24 48 40 00 	lea    0x4048(%rsp),%rax
  40268d:	00 
  40268e:	50                   	push   %rax
  40268f:	4d 89 f9             	mov    %r15,%r9
  402692:	4d 89 f0             	mov    %r14,%r8
  402695:	b9 58 35 40 00       	mov    $0x403558,%ecx
  40269a:	ba 00 20 00 00       	mov    $0x2000,%edx
  40269f:	be 01 00 00 00       	mov    $0x1,%esi
  4026a4:	4c 89 ef             	mov    %r13,%rdi
  4026a7:	b8 00 00 00 00       	mov    $0x0,%eax
  4026ac:	e8 cf e7 ff ff       	callq  400e80 <__sprintf_chk@plt>
  4026b1:	b8 00 00 00 00       	mov    $0x0,%eax
  4026b6:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4026bd:	4c 89 ef             	mov    %r13,%rdi
  4026c0:	f2 ae                	repnz scas %es:(%rdi),%al
  4026c2:	48 f7 d1             	not    %rcx
  4026c5:	48 8d 51 ff          	lea    -0x1(%rcx),%rdx
  4026c9:	4c 89 ee             	mov    %r13,%rsi
  4026cc:	89 ef                	mov    %ebp,%edi
  4026ce:	e8 b1 f9 ff ff       	callq  402084 <rio_writen>
  4026d3:	48 83 c4 10          	add    $0x10,%rsp
  4026d7:	48 85 c0             	test   %rax,%rax
  4026da:	79 6e                	jns    40274a <submitr+0x428>
  4026dc:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4026e3:	3a 20 43 
  4026e6:	48 89 03             	mov    %rax,(%rbx)
  4026e9:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4026f0:	20 75 6e 
  4026f3:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4026f7:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4026fe:	74 6f 20 
  402701:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402705:	48 b8 77 72 69 74 65 	movabs $0x6f74206574697277,%rax
  40270c:	20 74 6f 
  40270f:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402713:	48 b8 20 74 68 65 20 	movabs $0x7365722065687420,%rax
  40271a:	72 65 73 
  40271d:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402721:	48 b8 75 6c 74 20 73 	movabs $0x7672657320746c75,%rax
  402728:	65 72 76 
  40272b:	48 89 43 28          	mov    %rax,0x28(%rbx)
  40272f:	66 c7 43 30 65 72    	movw   $0x7265,0x30(%rbx)
  402735:	c6 43 32 00          	movb   $0x0,0x32(%rbx)
  402739:	89 ef                	mov    %ebp,%edi
  40273b:	e8 f0 e5 ff ff       	callq  400d30 <close@plt>
  402740:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402745:	e9 1e 03 00 00       	jmpq   402a68 <submitr+0x746>
  40274a:	89 ee                	mov    %ebp,%esi
  40274c:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  402751:	e8 ee f8 ff ff       	callq  402044 <rio_readinitb>
  402756:	ba 00 20 00 00       	mov    $0x2000,%edx
  40275b:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  402762:	00 
  402763:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  402768:	e8 fe f9 ff ff       	callq  40216b <rio_readlineb>
  40276d:	48 85 c0             	test   %rax,%rax
  402770:	7f 7d                	jg     4027ef <submitr+0x4cd>
  402772:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402779:	3a 20 43 
  40277c:	48 89 03             	mov    %rax,(%rbx)
  40277f:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402786:	20 75 6e 
  402789:	48 89 43 08          	mov    %rax,0x8(%rbx)
  40278d:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402794:	74 6f 20 
  402797:	48 89 43 10          	mov    %rax,0x10(%rbx)
  40279b:	48 b8 72 65 61 64 20 	movabs $0x7269662064616572,%rax
  4027a2:	66 69 72 
  4027a5:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4027a9:	48 b8 73 74 20 68 65 	movabs $0x6564616568207473,%rax
  4027b0:	61 64 65 
  4027b3:	48 89 43 20          	mov    %rax,0x20(%rbx)
  4027b7:	48 b8 72 20 66 72 6f 	movabs $0x72206d6f72662072,%rax
  4027be:	6d 20 72 
  4027c1:	48 89 43 28          	mov    %rax,0x28(%rbx)
  4027c5:	48 b8 65 73 75 6c 74 	movabs $0x657320746c757365,%rax
  4027cc:	20 73 65 
  4027cf:	48 89 43 30          	mov    %rax,0x30(%rbx)
  4027d3:	c7 43 38 72 76 65 72 	movl   $0x72657672,0x38(%rbx)
  4027da:	c6 43 3c 00          	movb   $0x0,0x3c(%rbx)
  4027de:	89 ef                	mov    %ebp,%edi
  4027e0:	e8 4b e5 ff ff       	callq  400d30 <close@plt>
  4027e5:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4027ea:	e9 79 02 00 00       	jmpq   402a68 <submitr+0x746>
  4027ef:	4c 8d 84 24 40 80 00 	lea    0x8040(%rsp),%r8
  4027f6:	00 
  4027f7:	48 8d 4c 24 1c       	lea    0x1c(%rsp),%rcx
  4027fc:	48 8d 94 24 40 60 00 	lea    0x6040(%rsp),%rdx
  402803:	00 
  402804:	be cf 35 40 00       	mov    $0x4035cf,%esi
  402809:	48 8d bc 24 40 20 00 	lea    0x2040(%rsp),%rdi
  402810:	00 
  402811:	b8 00 00 00 00       	mov    $0x0,%eax
  402816:	e8 c5 e5 ff ff       	callq  400de0 <__isoc99_sscanf@plt>
  40281b:	e9 95 00 00 00       	jmpq   4028b5 <submitr+0x593>
  402820:	ba 00 20 00 00       	mov    $0x2000,%edx
  402825:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  40282c:	00 
  40282d:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  402832:	e8 34 f9 ff ff       	callq  40216b <rio_readlineb>
  402837:	48 85 c0             	test   %rax,%rax
  40283a:	7f 79                	jg     4028b5 <submitr+0x593>
  40283c:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402843:	3a 20 43 
  402846:	48 89 03             	mov    %rax,(%rbx)
  402849:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402850:	20 75 6e 
  402853:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402857:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  40285e:	74 6f 20 
  402861:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402865:	48 b8 72 65 61 64 20 	movabs $0x6165682064616572,%rax
  40286c:	68 65 61 
  40286f:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402873:	48 b8 64 65 72 73 20 	movabs $0x6f72662073726564,%rax
  40287a:	66 72 6f 
  40287d:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402881:	48 b8 6d 20 74 68 65 	movabs $0x657220656874206d,%rax
  402888:	20 72 65 
  40288b:	48 89 43 28          	mov    %rax,0x28(%rbx)
  40288f:	48 b8 73 75 6c 74 20 	movabs $0x72657320746c7573,%rax
  402896:	73 65 72 
  402899:	48 89 43 30          	mov    %rax,0x30(%rbx)
  40289d:	c7 43 38 76 65 72 00 	movl   $0x726576,0x38(%rbx)
  4028a4:	89 ef                	mov    %ebp,%edi
  4028a6:	e8 85 e4 ff ff       	callq  400d30 <close@plt>
  4028ab:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4028b0:	e9 b3 01 00 00       	jmpq   402a68 <submitr+0x746>
  4028b5:	0f b6 94 24 40 20 00 	movzbl 0x2040(%rsp),%edx
  4028bc:	00 
  4028bd:	b8 0d 00 00 00       	mov    $0xd,%eax
  4028c2:	29 d0                	sub    %edx,%eax
  4028c4:	75 1b                	jne    4028e1 <submitr+0x5bf>
  4028c6:	0f b6 94 24 41 20 00 	movzbl 0x2041(%rsp),%edx
  4028cd:	00 
  4028ce:	b8 0a 00 00 00       	mov    $0xa,%eax
  4028d3:	29 d0                	sub    %edx,%eax
  4028d5:	75 0a                	jne    4028e1 <submitr+0x5bf>
  4028d7:	0f b6 84 24 42 20 00 	movzbl 0x2042(%rsp),%eax
  4028de:	00 
  4028df:	f7 d8                	neg    %eax
  4028e1:	85 c0                	test   %eax,%eax
  4028e3:	0f 85 37 ff ff ff    	jne    402820 <submitr+0x4fe>
  4028e9:	ba 00 20 00 00       	mov    $0x2000,%edx
  4028ee:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  4028f5:	00 
  4028f6:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  4028fb:	e8 6b f8 ff ff       	callq  40216b <rio_readlineb>
  402900:	48 85 c0             	test   %rax,%rax
  402903:	0f 8f 83 00 00 00    	jg     40298c <submitr+0x66a>
  402909:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402910:	3a 20 43 
  402913:	48 89 03             	mov    %rax,(%rbx)
  402916:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  40291d:	20 75 6e 
  402920:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402924:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  40292b:	74 6f 20 
  40292e:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402932:	48 b8 72 65 61 64 20 	movabs $0x6174732064616572,%rax
  402939:	73 74 61 
  40293c:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402940:	48 b8 74 75 73 20 6d 	movabs $0x7373656d20737574,%rax
  402947:	65 73 73 
  40294a:	48 89 43 20          	mov    %rax,0x20(%rbx)
  40294e:	48 b8 61 67 65 20 66 	movabs $0x6d6f726620656761,%rax
  402955:	72 6f 6d 
  402958:	48 89 43 28          	mov    %rax,0x28(%rbx)
  40295c:	48 b8 20 72 65 73 75 	movabs $0x20746c7573657220,%rax
  402963:	6c 74 20 
  402966:	48 89 43 30          	mov    %rax,0x30(%rbx)
  40296a:	c7 43 38 73 65 72 76 	movl   $0x76726573,0x38(%rbx)
  402971:	66 c7 43 3c 65 72    	movw   $0x7265,0x3c(%rbx)
  402977:	c6 43 3e 00          	movb   $0x0,0x3e(%rbx)
  40297b:	89 ef                	mov    %ebp,%edi
  40297d:	e8 ae e3 ff ff       	callq  400d30 <close@plt>
  402982:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402987:	e9 dc 00 00 00       	jmpq   402a68 <submitr+0x746>
  40298c:	44 8b 44 24 1c       	mov    0x1c(%rsp),%r8d
  402991:	41 81 f8 c8 00 00 00 	cmp    $0xc8,%r8d
  402998:	74 37                	je     4029d1 <submitr+0x6af>
  40299a:	4c 8d 8c 24 40 80 00 	lea    0x8040(%rsp),%r9
  4029a1:	00 
  4029a2:	b9 98 35 40 00       	mov    $0x403598,%ecx
  4029a7:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  4029ae:	be 01 00 00 00       	mov    $0x1,%esi
  4029b3:	48 89 df             	mov    %rbx,%rdi
  4029b6:	b8 00 00 00 00       	mov    $0x0,%eax
  4029bb:	e8 c0 e4 ff ff       	callq  400e80 <__sprintf_chk@plt>
  4029c0:	89 ef                	mov    %ebp,%edi
  4029c2:	e8 69 e3 ff ff       	callq  400d30 <close@plt>
  4029c7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4029cc:	e9 97 00 00 00       	jmpq   402a68 <submitr+0x746>
  4029d1:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  4029d8:	00 
  4029d9:	48 89 df             	mov    %rbx,%rdi
  4029dc:	e8 df e2 ff ff       	callq  400cc0 <strcpy@plt>
  4029e1:	89 ef                	mov    %ebp,%edi
  4029e3:	e8 48 e3 ff ff       	callq  400d30 <close@plt>
  4029e8:	0f b6 03             	movzbl (%rbx),%eax
  4029eb:	ba 4f 00 00 00       	mov    $0x4f,%edx
  4029f0:	29 c2                	sub    %eax,%edx
  4029f2:	75 22                	jne    402a16 <submitr+0x6f4>
  4029f4:	0f b6 4b 01          	movzbl 0x1(%rbx),%ecx
  4029f8:	b8 4b 00 00 00       	mov    $0x4b,%eax
  4029fd:	29 c8                	sub    %ecx,%eax
  4029ff:	75 17                	jne    402a18 <submitr+0x6f6>
  402a01:	0f b6 4b 02          	movzbl 0x2(%rbx),%ecx
  402a05:	b8 0a 00 00 00       	mov    $0xa,%eax
  402a0a:	29 c8                	sub    %ecx,%eax
  402a0c:	75 0a                	jne    402a18 <submitr+0x6f6>
  402a0e:	0f b6 43 03          	movzbl 0x3(%rbx),%eax
  402a12:	f7 d8                	neg    %eax
  402a14:	eb 02                	jmp    402a18 <submitr+0x6f6>
  402a16:	89 d0                	mov    %edx,%eax
  402a18:	85 c0                	test   %eax,%eax
  402a1a:	74 40                	je     402a5c <submitr+0x73a>
  402a1c:	bf e0 35 40 00       	mov    $0x4035e0,%edi
  402a21:	b9 05 00 00 00       	mov    $0x5,%ecx
  402a26:	48 89 de             	mov    %rbx,%rsi
  402a29:	f3 a6                	repz cmpsb %es:(%rdi),%ds:(%rsi)
  402a2b:	0f 97 c0             	seta   %al
  402a2e:	0f 92 c1             	setb   %cl
  402a31:	29 c8                	sub    %ecx,%eax
  402a33:	0f be c0             	movsbl %al,%eax
  402a36:	85 c0                	test   %eax,%eax
  402a38:	74 2e                	je     402a68 <submitr+0x746>
  402a3a:	85 d2                	test   %edx,%edx
  402a3c:	75 13                	jne    402a51 <submitr+0x72f>
  402a3e:	0f b6 43 01          	movzbl 0x1(%rbx),%eax
  402a42:	ba 4b 00 00 00       	mov    $0x4b,%edx
  402a47:	29 c2                	sub    %eax,%edx
  402a49:	75 06                	jne    402a51 <submitr+0x72f>
  402a4b:	0f b6 53 02          	movzbl 0x2(%rbx),%edx
  402a4f:	f7 da                	neg    %edx
  402a51:	85 d2                	test   %edx,%edx
  402a53:	75 0e                	jne    402a63 <submitr+0x741>
  402a55:	b8 00 00 00 00       	mov    $0x0,%eax
  402a5a:	eb 0c                	jmp    402a68 <submitr+0x746>
  402a5c:	b8 00 00 00 00       	mov    $0x0,%eax
  402a61:	eb 05                	jmp    402a68 <submitr+0x746>
  402a63:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402a68:	48 8b 9c 24 48 a0 00 	mov    0xa048(%rsp),%rbx
  402a6f:	00 
  402a70:	64 48 33 1c 25 28 00 	xor    %fs:0x28,%rbx
  402a77:	00 00 
  402a79:	74 05                	je     402a80 <submitr+0x75e>
  402a7b:	e8 70 e2 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  402a80:	48 81 c4 58 a0 00 00 	add    $0xa058,%rsp
  402a87:	5b                   	pop    %rbx
  402a88:	5d                   	pop    %rbp
  402a89:	41 5c                	pop    %r12
  402a8b:	41 5d                	pop    %r13
  402a8d:	41 5e                	pop    %r14
  402a8f:	41 5f                	pop    %r15
  402a91:	c3                   	retq   

0000000000402a92 <init_timeout>:
  402a92:	85 ff                	test   %edi,%edi
  402a94:	74 23                	je     402ab9 <init_timeout+0x27>
  402a96:	53                   	push   %rbx
  402a97:	89 fb                	mov    %edi,%ebx
  402a99:	85 ff                	test   %edi,%edi
  402a9b:	79 05                	jns    402aa2 <init_timeout+0x10>
  402a9d:	bb 00 00 00 00       	mov    $0x0,%ebx
  402aa2:	be 56 20 40 00       	mov    $0x402056,%esi
  402aa7:	bf 0e 00 00 00       	mov    $0xe,%edi
  402aac:	e8 af e2 ff ff       	callq  400d60 <signal@plt>
  402ab1:	89 df                	mov    %ebx,%edi
  402ab3:	e8 68 e2 ff ff       	callq  400d20 <alarm@plt>
  402ab8:	5b                   	pop    %rbx
  402ab9:	f3 c3                	repz retq 

0000000000402abb <init_driver>:
  402abb:	55                   	push   %rbp
  402abc:	53                   	push   %rbx
  402abd:	48 83 ec 28          	sub    $0x28,%rsp
  402ac1:	48 89 fd             	mov    %rdi,%rbp
  402ac4:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  402acb:	00 00 
  402acd:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  402ad2:	31 c0                	xor    %eax,%eax
  402ad4:	be 01 00 00 00       	mov    $0x1,%esi
  402ad9:	bf 0d 00 00 00       	mov    $0xd,%edi
  402ade:	e8 7d e2 ff ff       	callq  400d60 <signal@plt>
  402ae3:	be 01 00 00 00       	mov    $0x1,%esi
  402ae8:	bf 1d 00 00 00       	mov    $0x1d,%edi
  402aed:	e8 6e e2 ff ff       	callq  400d60 <signal@plt>
  402af2:	be 01 00 00 00       	mov    $0x1,%esi
  402af7:	bf 1d 00 00 00       	mov    $0x1d,%edi
  402afc:	e8 5f e2 ff ff       	callq  400d60 <signal@plt>
  402b01:	ba 00 00 00 00       	mov    $0x0,%edx
  402b06:	be 01 00 00 00       	mov    $0x1,%esi
  402b0b:	bf 02 00 00 00       	mov    $0x2,%edi
  402b10:	e8 7b e3 ff ff       	callq  400e90 <socket@plt>
  402b15:	85 c0                	test   %eax,%eax
  402b17:	79 4f                	jns    402b68 <init_driver+0xad>
  402b19:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402b20:	3a 20 43 
  402b23:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402b27:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402b2e:	20 75 6e 
  402b31:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402b35:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402b3c:	74 6f 20 
  402b3f:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402b43:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  402b4a:	65 20 73 
  402b4d:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402b51:	c7 45 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbp)
  402b58:	66 c7 45 24 74 00    	movw   $0x74,0x24(%rbp)
  402b5e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402b63:	e9 2a 01 00 00       	jmpq   402c92 <init_driver+0x1d7>
  402b68:	89 c3                	mov    %eax,%ebx
  402b6a:	bf e5 35 40 00       	mov    $0x4035e5,%edi
  402b6f:	e8 fc e1 ff ff       	callq  400d70 <gethostbyname@plt>
  402b74:	48 85 c0             	test   %rax,%rax
  402b77:	75 68                	jne    402be1 <init_driver+0x126>
  402b79:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  402b80:	3a 20 44 
  402b83:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402b87:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  402b8e:	20 75 6e 
  402b91:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402b95:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402b9c:	74 6f 20 
  402b9f:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402ba3:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  402baa:	76 65 20 
  402bad:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402bb1:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  402bb8:	72 20 61 
  402bbb:	48 89 45 20          	mov    %rax,0x20(%rbp)
  402bbf:	c7 45 28 64 64 72 65 	movl   $0x65726464,0x28(%rbp)
  402bc6:	66 c7 45 2c 73 73    	movw   $0x7373,0x2c(%rbp)
  402bcc:	c6 45 2e 00          	movb   $0x0,0x2e(%rbp)
  402bd0:	89 df                	mov    %ebx,%edi
  402bd2:	e8 59 e1 ff ff       	callq  400d30 <close@plt>
  402bd7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402bdc:	e9 b1 00 00 00       	jmpq   402c92 <init_driver+0x1d7>
  402be1:	48 c7 04 24 00 00 00 	movq   $0x0,(%rsp)
  402be8:	00 
  402be9:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  402bf0:	00 00 
  402bf2:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
  402bf8:	48 63 50 14          	movslq 0x14(%rax),%rdx
  402bfc:	48 8b 40 18          	mov    0x18(%rax),%rax
  402c00:	48 8b 30             	mov    (%rax),%rsi
  402c03:	48 8d 7c 24 04       	lea    0x4(%rsp),%rdi
  402c08:	b9 0c 00 00 00       	mov    $0xc,%ecx
  402c0d:	e8 6e e1 ff ff       	callq  400d80 <__memmove_chk@plt>
  402c12:	66 c7 44 24 02 3c 9a 	movw   $0x9a3c,0x2(%rsp)
  402c19:	ba 10 00 00 00       	mov    $0x10,%edx
  402c1e:	48 89 e6             	mov    %rsp,%rsi
  402c21:	89 df                	mov    %ebx,%edi
  402c23:	e8 38 e2 ff ff       	callq  400e60 <connect@plt>
  402c28:	85 c0                	test   %eax,%eax
  402c2a:	79 50                	jns    402c7c <init_driver+0x1c1>
  402c2c:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  402c33:	3a 20 55 
  402c36:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402c3a:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  402c41:	20 74 6f 
  402c44:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402c48:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  402c4f:	65 63 74 
  402c52:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402c56:	48 b8 20 74 6f 20 73 	movabs $0x76726573206f7420,%rax
  402c5d:	65 72 76 
  402c60:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402c64:	66 c7 45 20 65 72    	movw   $0x7265,0x20(%rbp)
  402c6a:	c6 45 22 00          	movb   $0x0,0x22(%rbp)
  402c6e:	89 df                	mov    %ebx,%edi
  402c70:	e8 bb e0 ff ff       	callq  400d30 <close@plt>
  402c75:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402c7a:	eb 16                	jmp    402c92 <init_driver+0x1d7>
  402c7c:	89 df                	mov    %ebx,%edi
  402c7e:	e8 ad e0 ff ff       	callq  400d30 <close@plt>
  402c83:	66 c7 45 00 4f 4b    	movw   $0x4b4f,0x0(%rbp)
  402c89:	c6 45 02 00          	movb   $0x0,0x2(%rbp)
  402c8d:	b8 00 00 00 00       	mov    $0x0,%eax
  402c92:	48 8b 4c 24 18       	mov    0x18(%rsp),%rcx
  402c97:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  402c9e:	00 00 
  402ca0:	74 05                	je     402ca7 <init_driver+0x1ec>
  402ca2:	e8 49 e0 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  402ca7:	48 83 c4 28          	add    $0x28,%rsp
  402cab:	5b                   	pop    %rbx
  402cac:	5d                   	pop    %rbp
  402cad:	c3                   	retq   

0000000000402cae <driver_post>:
  402cae:	53                   	push   %rbx
  402caf:	4c 89 cb             	mov    %r9,%rbx
  402cb2:	45 85 c0             	test   %r8d,%r8d
  402cb5:	74 27                	je     402cde <driver_post+0x30>
  402cb7:	48 89 ca             	mov    %rcx,%rdx
  402cba:	be fd 35 40 00       	mov    $0x4035fd,%esi
  402cbf:	bf 01 00 00 00       	mov    $0x1,%edi
  402cc4:	b8 00 00 00 00       	mov    $0x0,%eax
  402cc9:	e8 32 e1 ff ff       	callq  400e00 <__printf_chk@plt>
  402cce:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  402cd3:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  402cd7:	b8 00 00 00 00       	mov    $0x0,%eax
  402cdc:	eb 3f                	jmp    402d1d <driver_post+0x6f>
  402cde:	48 85 ff             	test   %rdi,%rdi
  402ce1:	74 2c                	je     402d0f <driver_post+0x61>
  402ce3:	80 3f 00             	cmpb   $0x0,(%rdi)
  402ce6:	74 27                	je     402d0f <driver_post+0x61>
  402ce8:	48 83 ec 08          	sub    $0x8,%rsp
  402cec:	41 51                	push   %r9
  402cee:	49 89 c9             	mov    %rcx,%r9
  402cf1:	49 89 d0             	mov    %rdx,%r8
  402cf4:	48 89 f9             	mov    %rdi,%rcx
  402cf7:	48 89 f2             	mov    %rsi,%rdx
  402cfa:	be 9a 3c 00 00       	mov    $0x3c9a,%esi
  402cff:	bf e5 35 40 00       	mov    $0x4035e5,%edi
  402d04:	e8 19 f6 ff ff       	callq  402322 <submitr>
  402d09:	48 83 c4 10          	add    $0x10,%rsp
  402d0d:	eb 0e                	jmp    402d1d <driver_post+0x6f>
  402d0f:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  402d14:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  402d18:	b8 00 00 00 00       	mov    $0x0,%eax
  402d1d:	5b                   	pop    %rbx
  402d1e:	c3                   	retq   

0000000000402d1f <check>:
  402d1f:	89 f8                	mov    %edi,%eax
  402d21:	c1 e8 1c             	shr    $0x1c,%eax
  402d24:	85 c0                	test   %eax,%eax
  402d26:	74 1d                	je     402d45 <check+0x26>
  402d28:	b9 00 00 00 00       	mov    $0x0,%ecx
  402d2d:	eb 0b                	jmp    402d3a <check+0x1b>
  402d2f:	89 f8                	mov    %edi,%eax
  402d31:	d3 e8                	shr    %cl,%eax
  402d33:	3c 0a                	cmp    $0xa,%al
  402d35:	74 14                	je     402d4b <check+0x2c>
  402d37:	83 c1 08             	add    $0x8,%ecx
  402d3a:	83 f9 1f             	cmp    $0x1f,%ecx
  402d3d:	7e f0                	jle    402d2f <check+0x10>
  402d3f:	b8 01 00 00 00       	mov    $0x1,%eax
  402d44:	c3                   	retq   
  402d45:	b8 00 00 00 00       	mov    $0x0,%eax
  402d4a:	c3                   	retq   
  402d4b:	b8 00 00 00 00       	mov    $0x0,%eax
  402d50:	c3                   	retq   

0000000000402d51 <gencookie>:
  402d51:	53                   	push   %rbx
  402d52:	83 c7 01             	add    $0x1,%edi
  402d55:	e8 46 df ff ff       	callq  400ca0 <srandom@plt>
  402d5a:	e8 61 e0 ff ff       	callq  400dc0 <random@plt>
  402d5f:	89 c3                	mov    %eax,%ebx
  402d61:	89 c7                	mov    %eax,%edi
  402d63:	e8 b7 ff ff ff       	callq  402d1f <check>
  402d68:	85 c0                	test   %eax,%eax
  402d6a:	74 ee                	je     402d5a <gencookie+0x9>
  402d6c:	89 d8                	mov    %ebx,%eax
  402d6e:	5b                   	pop    %rbx
  402d6f:	c3                   	retq   

0000000000402d70 <__libc_csu_init>:
  402d70:	41 57                	push   %r15
  402d72:	41 56                	push   %r14
  402d74:	41 89 ff             	mov    %edi,%r15d
  402d77:	41 55                	push   %r13
  402d79:	41 54                	push   %r12
  402d7b:	4c 8d 25 8e 10 20 00 	lea    0x20108e(%rip),%r12        # 603e10 <__frame_dummy_init_array_entry>
  402d82:	55                   	push   %rbp
  402d83:	48 8d 2d 8e 10 20 00 	lea    0x20108e(%rip),%rbp        # 603e18 <__do_global_dtors_aux_fini_array_entry>
  402d8a:	53                   	push   %rbx
  402d8b:	49 89 f6             	mov    %rsi,%r14
  402d8e:	49 89 d5             	mov    %rdx,%r13
  402d91:	4c 29 e5             	sub    %r12,%rbp
  402d94:	48 83 ec 08          	sub    $0x8,%rsp
  402d98:	48 c1 fd 03          	sar    $0x3,%rbp
  402d9c:	e8 a7 de ff ff       	callq  400c48 <_init>
  402da1:	48 85 ed             	test   %rbp,%rbp
  402da4:	74 20                	je     402dc6 <__libc_csu_init+0x56>
  402da6:	31 db                	xor    %ebx,%ebx
  402da8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  402daf:	00 
  402db0:	4c 89 ea             	mov    %r13,%rdx
  402db3:	4c 89 f6             	mov    %r14,%rsi
  402db6:	44 89 ff             	mov    %r15d,%edi
  402db9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  402dbd:	48 83 c3 01          	add    $0x1,%rbx
  402dc1:	48 39 eb             	cmp    %rbp,%rbx
  402dc4:	75 ea                	jne    402db0 <__libc_csu_init+0x40>
  402dc6:	48 83 c4 08          	add    $0x8,%rsp
  402dca:	5b                   	pop    %rbx
  402dcb:	5d                   	pop    %rbp
  402dcc:	41 5c                	pop    %r12
  402dce:	41 5d                	pop    %r13
  402dd0:	41 5e                	pop    %r14
  402dd2:	41 5f                	pop    %r15
  402dd4:	c3                   	retq   
  402dd5:	90                   	nop
  402dd6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  402ddd:	00 00 00 

0000000000402de0 <__libc_csu_fini>:
  402de0:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000402de4 <_fini>:
  402de4:	48 83 ec 08          	sub    $0x8,%rsp
  402de8:	48 83 c4 08          	add    $0x8,%rsp
  402dec:	c3                   	retq   
