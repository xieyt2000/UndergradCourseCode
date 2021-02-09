
rtarget:     file format elf64-x86-64


Disassembly of section .init:

0000000000400c48 <_init>:
  400c48:	48 83 ec 08          	sub    $0x8,%rsp
  400c4c:	48 8b 05 a5 43 20 00 	mov    0x2043a5(%rip),%rax        # 604ff8 <__gmon_start__>
  400c53:	48 85 c0             	test   %rax,%rax
  400c56:	74 05                	je     400c5d <_init+0x15>
  400c58:	e8 43 02 00 00       	callq  400ea0 <__gmon_start__@plt>
  400c5d:	48 83 c4 08          	add    $0x8,%rsp
  400c61:	c3                   	retq   

Disassembly of section .plt:

0000000000400c70 <.plt>:
  400c70:	ff 35 92 43 20 00    	pushq  0x204392(%rip)        # 605008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400c76:	ff 25 94 43 20 00    	jmpq   *0x204394(%rip)        # 605010 <_GLOBAL_OFFSET_TABLE_+0x10>
  400c7c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400c80 <strcasecmp@plt>:
  400c80:	ff 25 92 43 20 00    	jmpq   *0x204392(%rip)        # 605018 <strcasecmp@GLIBC_2.2.5>
  400c86:	68 00 00 00 00       	pushq  $0x0
  400c8b:	e9 e0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400c90 <__errno_location@plt>:
  400c90:	ff 25 8a 43 20 00    	jmpq   *0x20438a(%rip)        # 605020 <__errno_location@GLIBC_2.2.5>
  400c96:	68 01 00 00 00       	pushq  $0x1
  400c9b:	e9 d0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400ca0 <srandom@plt>:
  400ca0:	ff 25 82 43 20 00    	jmpq   *0x204382(%rip)        # 605028 <srandom@GLIBC_2.2.5>
  400ca6:	68 02 00 00 00       	pushq  $0x2
  400cab:	e9 c0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cb0 <strncmp@plt>:
  400cb0:	ff 25 7a 43 20 00    	jmpq   *0x20437a(%rip)        # 605030 <strncmp@GLIBC_2.2.5>
  400cb6:	68 03 00 00 00       	pushq  $0x3
  400cbb:	e9 b0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cc0 <strcpy@plt>:
  400cc0:	ff 25 72 43 20 00    	jmpq   *0x204372(%rip)        # 605038 <strcpy@GLIBC_2.2.5>
  400cc6:	68 04 00 00 00       	pushq  $0x4
  400ccb:	e9 a0 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cd0 <puts@plt>:
  400cd0:	ff 25 6a 43 20 00    	jmpq   *0x20436a(%rip)        # 605040 <puts@GLIBC_2.2.5>
  400cd6:	68 05 00 00 00       	pushq  $0x5
  400cdb:	e9 90 ff ff ff       	jmpq   400c70 <.plt>

0000000000400ce0 <write@plt>:
  400ce0:	ff 25 62 43 20 00    	jmpq   *0x204362(%rip)        # 605048 <write@GLIBC_2.2.5>
  400ce6:	68 06 00 00 00       	pushq  $0x6
  400ceb:	e9 80 ff ff ff       	jmpq   400c70 <.plt>

0000000000400cf0 <__stack_chk_fail@plt>:
  400cf0:	ff 25 5a 43 20 00    	jmpq   *0x20435a(%rip)        # 605050 <__stack_chk_fail@GLIBC_2.4>
  400cf6:	68 07 00 00 00       	pushq  $0x7
  400cfb:	e9 70 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d00 <mmap@plt>:
  400d00:	ff 25 52 43 20 00    	jmpq   *0x204352(%rip)        # 605058 <mmap@GLIBC_2.2.5>
  400d06:	68 08 00 00 00       	pushq  $0x8
  400d0b:	e9 60 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d10 <memset@plt>:
  400d10:	ff 25 4a 43 20 00    	jmpq   *0x20434a(%rip)        # 605060 <memset@GLIBC_2.2.5>
  400d16:	68 09 00 00 00       	pushq  $0x9
  400d1b:	e9 50 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d20 <alarm@plt>:
  400d20:	ff 25 42 43 20 00    	jmpq   *0x204342(%rip)        # 605068 <alarm@GLIBC_2.2.5>
  400d26:	68 0a 00 00 00       	pushq  $0xa
  400d2b:	e9 40 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d30 <close@plt>:
  400d30:	ff 25 3a 43 20 00    	jmpq   *0x20433a(%rip)        # 605070 <close@GLIBC_2.2.5>
  400d36:	68 0b 00 00 00       	pushq  $0xb
  400d3b:	e9 30 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d40 <read@plt>:
  400d40:	ff 25 32 43 20 00    	jmpq   *0x204332(%rip)        # 605078 <read@GLIBC_2.2.5>
  400d46:	68 0c 00 00 00       	pushq  $0xc
  400d4b:	e9 20 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d50 <__libc_start_main@plt>:
  400d50:	ff 25 2a 43 20 00    	jmpq   *0x20432a(%rip)        # 605080 <__libc_start_main@GLIBC_2.2.5>
  400d56:	68 0d 00 00 00       	pushq  $0xd
  400d5b:	e9 10 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d60 <signal@plt>:
  400d60:	ff 25 22 43 20 00    	jmpq   *0x204322(%rip)        # 605088 <signal@GLIBC_2.2.5>
  400d66:	68 0e 00 00 00       	pushq  $0xe
  400d6b:	e9 00 ff ff ff       	jmpq   400c70 <.plt>

0000000000400d70 <gethostbyname@plt>:
  400d70:	ff 25 1a 43 20 00    	jmpq   *0x20431a(%rip)        # 605090 <gethostbyname@GLIBC_2.2.5>
  400d76:	68 0f 00 00 00       	pushq  $0xf
  400d7b:	e9 f0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400d80 <__memmove_chk@plt>:
  400d80:	ff 25 12 43 20 00    	jmpq   *0x204312(%rip)        # 605098 <__memmove_chk@GLIBC_2.3.4>
  400d86:	68 10 00 00 00       	pushq  $0x10
  400d8b:	e9 e0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400d90 <strtol@plt>:
  400d90:	ff 25 0a 43 20 00    	jmpq   *0x20430a(%rip)        # 6050a0 <strtol@GLIBC_2.2.5>
  400d96:	68 11 00 00 00       	pushq  $0x11
  400d9b:	e9 d0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400da0 <memcpy@plt>:
  400da0:	ff 25 02 43 20 00    	jmpq   *0x204302(%rip)        # 6050a8 <memcpy@GLIBC_2.14>
  400da6:	68 12 00 00 00       	pushq  $0x12
  400dab:	e9 c0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400db0 <time@plt>:
  400db0:	ff 25 fa 42 20 00    	jmpq   *0x2042fa(%rip)        # 6050b0 <time@GLIBC_2.2.5>
  400db6:	68 13 00 00 00       	pushq  $0x13
  400dbb:	e9 b0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400dc0 <random@plt>:
  400dc0:	ff 25 f2 42 20 00    	jmpq   *0x2042f2(%rip)        # 6050b8 <random@GLIBC_2.2.5>
  400dc6:	68 14 00 00 00       	pushq  $0x14
  400dcb:	e9 a0 fe ff ff       	jmpq   400c70 <.plt>

0000000000400dd0 <_IO_getc@plt>:
  400dd0:	ff 25 ea 42 20 00    	jmpq   *0x2042ea(%rip)        # 6050c0 <_IO_getc@GLIBC_2.2.5>
  400dd6:	68 15 00 00 00       	pushq  $0x15
  400ddb:	e9 90 fe ff ff       	jmpq   400c70 <.plt>

0000000000400de0 <__isoc99_sscanf@plt>:
  400de0:	ff 25 e2 42 20 00    	jmpq   *0x2042e2(%rip)        # 6050c8 <__isoc99_sscanf@GLIBC_2.7>
  400de6:	68 16 00 00 00       	pushq  $0x16
  400deb:	e9 80 fe ff ff       	jmpq   400c70 <.plt>

0000000000400df0 <munmap@plt>:
  400df0:	ff 25 da 42 20 00    	jmpq   *0x2042da(%rip)        # 6050d0 <munmap@GLIBC_2.2.5>
  400df6:	68 17 00 00 00       	pushq  $0x17
  400dfb:	e9 70 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e00 <__printf_chk@plt>:
  400e00:	ff 25 d2 42 20 00    	jmpq   *0x2042d2(%rip)        # 6050d8 <__printf_chk@GLIBC_2.3.4>
  400e06:	68 18 00 00 00       	pushq  $0x18
  400e0b:	e9 60 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e10 <fopen@plt>:
  400e10:	ff 25 ca 42 20 00    	jmpq   *0x2042ca(%rip)        # 6050e0 <fopen@GLIBC_2.2.5>
  400e16:	68 19 00 00 00       	pushq  $0x19
  400e1b:	e9 50 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e20 <getopt@plt>:
  400e20:	ff 25 c2 42 20 00    	jmpq   *0x2042c2(%rip)        # 6050e8 <getopt@GLIBC_2.2.5>
  400e26:	68 1a 00 00 00       	pushq  $0x1a
  400e2b:	e9 40 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e30 <strtoul@plt>:
  400e30:	ff 25 ba 42 20 00    	jmpq   *0x2042ba(%rip)        # 6050f0 <strtoul@GLIBC_2.2.5>
  400e36:	68 1b 00 00 00       	pushq  $0x1b
  400e3b:	e9 30 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e40 <gethostname@plt>:
  400e40:	ff 25 b2 42 20 00    	jmpq   *0x2042b2(%rip)        # 6050f8 <gethostname@GLIBC_2.2.5>
  400e46:	68 1c 00 00 00       	pushq  $0x1c
  400e4b:	e9 20 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e50 <exit@plt>:
  400e50:	ff 25 aa 42 20 00    	jmpq   *0x2042aa(%rip)        # 605100 <exit@GLIBC_2.2.5>
  400e56:	68 1d 00 00 00       	pushq  $0x1d
  400e5b:	e9 10 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e60 <connect@plt>:
  400e60:	ff 25 a2 42 20 00    	jmpq   *0x2042a2(%rip)        # 605108 <connect@GLIBC_2.2.5>
  400e66:	68 1e 00 00 00       	pushq  $0x1e
  400e6b:	e9 00 fe ff ff       	jmpq   400c70 <.plt>

0000000000400e70 <__fprintf_chk@plt>:
  400e70:	ff 25 9a 42 20 00    	jmpq   *0x20429a(%rip)        # 605110 <__fprintf_chk@GLIBC_2.3.4>
  400e76:	68 1f 00 00 00       	pushq  $0x1f
  400e7b:	e9 f0 fd ff ff       	jmpq   400c70 <.plt>

0000000000400e80 <__sprintf_chk@plt>:
  400e80:	ff 25 92 42 20 00    	jmpq   *0x204292(%rip)        # 605118 <__sprintf_chk@GLIBC_2.3.4>
  400e86:	68 20 00 00 00       	pushq  $0x20
  400e8b:	e9 e0 fd ff ff       	jmpq   400c70 <.plt>

0000000000400e90 <socket@plt>:
  400e90:	ff 25 8a 42 20 00    	jmpq   *0x20428a(%rip)        # 605120 <socket@GLIBC_2.2.5>
  400e96:	68 21 00 00 00       	pushq  $0x21
  400e9b:	e9 d0 fd ff ff       	jmpq   400c70 <.plt>

Disassembly of section .plt.got:

0000000000400ea0 <__gmon_start__@plt>:
  400ea0:	ff 25 52 41 20 00    	jmpq   *0x204152(%rip)        # 604ff8 <__gmon_start__>
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
  400ebf:	49 c7 c0 10 2f 40 00 	mov    $0x402f10,%r8
  400ec6:	48 c7 c1 a0 2e 40 00 	mov    $0x402ea0,%rcx
  400ecd:	48 c7 c7 b5 11 40 00 	mov    $0x4011b5,%rdi
  400ed4:	e8 77 fe ff ff       	callq  400d50 <__libc_start_main@plt>
  400ed9:	f4                   	hlt    
  400eda:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400ee0 <deregister_tm_clones>:
  400ee0:	b8 b7 54 60 00       	mov    $0x6054b7,%eax
  400ee5:	55                   	push   %rbp
  400ee6:	48 2d b0 54 60 00    	sub    $0x6054b0,%rax
  400eec:	48 83 f8 0e          	cmp    $0xe,%rax
  400ef0:	48 89 e5             	mov    %rsp,%rbp
  400ef3:	76 1b                	jbe    400f10 <deregister_tm_clones+0x30>
  400ef5:	b8 00 00 00 00       	mov    $0x0,%eax
  400efa:	48 85 c0             	test   %rax,%rax
  400efd:	74 11                	je     400f10 <deregister_tm_clones+0x30>
  400eff:	5d                   	pop    %rbp
  400f00:	bf b0 54 60 00       	mov    $0x6054b0,%edi
  400f05:	ff e0                	jmpq   *%rax
  400f07:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  400f0e:	00 00 
  400f10:	5d                   	pop    %rbp
  400f11:	c3                   	retq   
  400f12:	0f 1f 40 00          	nopl   0x0(%rax)
  400f16:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  400f1d:	00 00 00 

0000000000400f20 <register_tm_clones>:
  400f20:	be b0 54 60 00       	mov    $0x6054b0,%esi
  400f25:	55                   	push   %rbp
  400f26:	48 81 ee b0 54 60 00 	sub    $0x6054b0,%rsi
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
  400f4e:	bf b0 54 60 00       	mov    $0x6054b0,%edi
  400f53:	ff e0                	jmpq   *%rax
  400f55:	0f 1f 00             	nopl   (%rax)
  400f58:	5d                   	pop    %rbp
  400f59:	c3                   	retq   
  400f5a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000400f60 <__do_global_dtors_aux>:
  400f60:	80 3d 81 45 20 00 00 	cmpb   $0x0,0x204581(%rip)        # 6054e8 <completed.7594>
  400f67:	75 11                	jne    400f7a <__do_global_dtors_aux+0x1a>
  400f69:	55                   	push   %rbp
  400f6a:	48 89 e5             	mov    %rsp,%rbp
  400f6d:	e8 6e ff ff ff       	callq  400ee0 <deregister_tm_clones>
  400f72:	5d                   	pop    %rbp
  400f73:	c6 05 6e 45 20 00 01 	movb   $0x1,0x20456e(%rip)        # 6054e8 <completed.7594>
  400f7a:	f3 c3                	repz retq 
  400f7c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400f80 <frame_dummy>:
  400f80:	bf 20 4e 60 00       	mov    $0x604e20,%edi
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
  400fad:	83 3d 74 45 20 00 00 	cmpl   $0x0,0x204574(%rip)        # 605528 <is_checker>
  400fb4:	74 3e                	je     400ff4 <usage+0x4e>
  400fb6:	be 28 2f 40 00       	mov    $0x402f28,%esi
  400fbb:	bf 01 00 00 00       	mov    $0x1,%edi
  400fc0:	b8 00 00 00 00       	mov    $0x0,%eax
  400fc5:	e8 36 fe ff ff       	callq  400e00 <__printf_chk@plt>
  400fca:	bf 60 2f 40 00       	mov    $0x402f60,%edi
  400fcf:	e8 fc fc ff ff       	callq  400cd0 <puts@plt>
  400fd4:	bf d8 30 40 00       	mov    $0x4030d8,%edi
  400fd9:	e8 f2 fc ff ff       	callq  400cd0 <puts@plt>
  400fde:	bf 88 2f 40 00       	mov    $0x402f88,%edi
  400fe3:	e8 e8 fc ff ff       	callq  400cd0 <puts@plt>
  400fe8:	bf f2 30 40 00       	mov    $0x4030f2,%edi
  400fed:	e8 de fc ff ff       	callq  400cd0 <puts@plt>
  400ff2:	eb 32                	jmp    401026 <usage+0x80>
  400ff4:	be 0e 31 40 00       	mov    $0x40310e,%esi
  400ff9:	bf 01 00 00 00       	mov    $0x1,%edi
  400ffe:	b8 00 00 00 00       	mov    $0x0,%eax
  401003:	e8 f8 fd ff ff       	callq  400e00 <__printf_chk@plt>
  401008:	bf b0 2f 40 00       	mov    $0x402fb0,%edi
  40100d:	e8 be fc ff ff       	callq  400cd0 <puts@plt>
  401012:	bf d8 2f 40 00       	mov    $0x402fd8,%edi
  401017:	e8 b4 fc ff ff       	callq  400cd0 <puts@plt>
  40101c:	bf 2c 31 40 00       	mov    $0x40312c,%edi
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
  40104e:	89 3d c4 44 20 00    	mov    %edi,0x2044c4(%rip)        # 605518 <check_level>
  401054:	8b 3d 0e 41 20 00    	mov    0x20410e(%rip),%edi        # 605168 <target_id>
  40105a:	e8 14 1e 00 00       	callq  402e73 <gencookie>
  40105f:	89 05 bf 44 20 00    	mov    %eax,0x2044bf(%rip)        # 605524 <cookie>
  401065:	89 c7                	mov    %eax,%edi
  401067:	e8 07 1e 00 00       	callq  402e73 <gencookie>
  40106c:	89 05 ae 44 20 00    	mov    %eax,0x2044ae(%rip)        # 605520 <authkey>
  401072:	8b 05 f0 40 20 00    	mov    0x2040f0(%rip),%eax        # 605168 <target_id>
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
  4010bd:	48 89 05 dc 43 20 00 	mov    %rax,0x2043dc(%rip)        # 6054a0 <buf_offset>
  4010c4:	c6 05 7d 50 20 00 72 	movb   $0x72,0x20507d(%rip)        # 606148 <target_prefix>
  4010cb:	83 3d d6 43 20 00 00 	cmpl   $0x0,0x2043d6(%rip)        # 6054a8 <notify>
  4010d2:	0f 84 bb 00 00 00    	je     401193 <initialize_target+0x163>
  4010d8:	83 3d 49 44 20 00 00 	cmpl   $0x0,0x204449(%rip)        # 605528 <is_checker>
  4010df:	0f 85 ae 00 00 00    	jne    401193 <initialize_target+0x163>
  4010e5:	be 00 01 00 00       	mov    $0x100,%esi
  4010ea:	48 89 e7             	mov    %rsp,%rdi
  4010ed:	e8 4e fd ff ff       	callq  400e40 <gethostname@plt>
  4010f2:	85 c0                	test   %eax,%eax
  4010f4:	74 25                	je     40111b <initialize_target+0xeb>
  4010f6:	bf 08 30 40 00       	mov    $0x403008,%edi
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
  401123:	48 8b 3c c5 80 51 60 	mov    0x605180(,%rax,8),%rdi
  40112a:	00 
  40112b:	48 85 ff             	test   %rdi,%rdi
  40112e:	75 da                	jne    40110a <initialize_target+0xda>
  401130:	b8 00 00 00 00       	mov    $0x0,%eax
  401135:	eb 05                	jmp    40113c <initialize_target+0x10c>
  401137:	b8 01 00 00 00       	mov    $0x1,%eax
  40113c:	85 c0                	test   %eax,%eax
  40113e:	75 1c                	jne    40115c <initialize_target+0x12c>
  401140:	48 89 e2             	mov    %rsp,%rdx
  401143:	be 40 30 40 00       	mov    $0x403040,%esi
  401148:	bf 01 00 00 00       	mov    $0x1,%edi
  40114d:	e8 ae fc ff ff       	callq  400e00 <__printf_chk@plt>
  401152:	bf 08 00 00 00       	mov    $0x8,%edi
  401157:	e8 f4 fc ff ff       	callq  400e50 <exit@plt>
  40115c:	48 8d bc 24 00 01 00 	lea    0x100(%rsp),%rdi
  401163:	00 
  401164:	e8 74 1a 00 00       	callq  402bdd <init_driver>
  401169:	85 c0                	test   %eax,%eax
  40116b:	79 26                	jns    401193 <initialize_target+0x163>
  40116d:	48 8d 94 24 00 01 00 	lea    0x100(%rsp),%rdx
  401174:	00 
  401175:	be 80 30 40 00       	mov    $0x403080,%esi
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
  4011c3:	be 18 1f 40 00       	mov    $0x401f18,%esi
  4011c8:	bf 0b 00 00 00       	mov    $0xb,%edi
  4011cd:	e8 8e fb ff ff       	callq  400d60 <signal@plt>
  4011d2:	be ca 1e 40 00       	mov    $0x401eca,%esi
  4011d7:	bf 07 00 00 00       	mov    $0x7,%edi
  4011dc:	e8 7f fb ff ff       	callq  400d60 <signal@plt>
  4011e1:	be 66 1f 40 00       	mov    $0x401f66,%esi
  4011e6:	bf 04 00 00 00       	mov    $0x4,%edi
  4011eb:	e8 70 fb ff ff       	callq  400d60 <signal@plt>
  4011f0:	83 3d 31 43 20 00 00 	cmpl   $0x0,0x204331(%rip)        # 605528 <is_checker>
  4011f7:	74 20                	je     401219 <main+0x64>
  4011f9:	be b4 1f 40 00       	mov    $0x401fb4,%esi
  4011fe:	bf 0e 00 00 00       	mov    $0xe,%edi
  401203:	e8 58 fb ff ff       	callq  400d60 <signal@plt>
  401208:	bf 05 00 00 00       	mov    $0x5,%edi
  40120d:	e8 0e fb ff ff       	callq  400d20 <alarm@plt>
  401212:	bd 4a 31 40 00       	mov    $0x40314a,%ebp
  401217:	eb 05                	jmp    40121e <main+0x69>
  401219:	bd 45 31 40 00       	mov    $0x403145,%ebp
  40121e:	48 8b 05 9b 42 20 00 	mov    0x20429b(%rip),%rax        # 6054c0 <stdin@@GLIBC_2.2.5>
  401225:	48 89 05 e4 42 20 00 	mov    %rax,0x2042e4(%rip)        # 605510 <infile>
  40122c:	41 bd 00 00 00 00    	mov    $0x0,%r13d
  401232:	41 be 00 00 00 00    	mov    $0x0,%r14d
  401238:	e9 c6 00 00 00       	jmpq   401303 <main+0x14e>
  40123d:	83 e8 61             	sub    $0x61,%eax
  401240:	3c 10                	cmp    $0x10,%al
  401242:	0f 87 9c 00 00 00    	ja     4012e4 <main+0x12f>
  401248:	0f b6 c0             	movzbl %al,%eax
  40124b:	ff 24 c5 90 31 40 00 	jmpq   *0x403190(,%rax,8)
  401252:	48 8b 3b             	mov    (%rbx),%rdi
  401255:	e8 4c fd ff ff       	callq  400fa6 <usage>
  40125a:	be 0d 34 40 00       	mov    $0x40340d,%esi
  40125f:	48 8b 3d 62 42 20 00 	mov    0x204262(%rip),%rdi        # 6054c8 <optarg@@GLIBC_2.2.5>
  401266:	e8 a5 fb ff ff       	callq  400e10 <fopen@plt>
  40126b:	48 89 05 9e 42 20 00 	mov    %rax,0x20429e(%rip)        # 605510 <infile>
  401272:	48 85 c0             	test   %rax,%rax
  401275:	0f 85 88 00 00 00    	jne    401303 <main+0x14e>
  40127b:	48 8b 0d 46 42 20 00 	mov    0x204246(%rip),%rcx        # 6054c8 <optarg@@GLIBC_2.2.5>
  401282:	ba 52 31 40 00       	mov    $0x403152,%edx
  401287:	be 01 00 00 00       	mov    $0x1,%esi
  40128c:	48 8b 3d 4d 42 20 00 	mov    0x20424d(%rip),%rdi        # 6054e0 <stderr@@GLIBC_2.2.5>
  401293:	e8 d8 fb ff ff       	callq  400e70 <__fprintf_chk@plt>
  401298:	b8 01 00 00 00       	mov    $0x1,%eax
  40129d:	e9 e4 00 00 00       	jmpq   401386 <main+0x1d1>
  4012a2:	ba 10 00 00 00       	mov    $0x10,%edx
  4012a7:	be 00 00 00 00       	mov    $0x0,%esi
  4012ac:	48 8b 3d 15 42 20 00 	mov    0x204215(%rip),%rdi        # 6054c8 <optarg@@GLIBC_2.2.5>
  4012b3:	e8 78 fb ff ff       	callq  400e30 <strtoul@plt>
  4012b8:	41 89 c6             	mov    %eax,%r14d
  4012bb:	eb 46                	jmp    401303 <main+0x14e>
  4012bd:	ba 0a 00 00 00       	mov    $0xa,%edx
  4012c2:	be 00 00 00 00       	mov    $0x0,%esi
  4012c7:	48 8b 3d fa 41 20 00 	mov    0x2041fa(%rip),%rdi        # 6054c8 <optarg@@GLIBC_2.2.5>
  4012ce:	e8 bd fa ff ff       	callq  400d90 <strtol@plt>
  4012d3:	41 89 c5             	mov    %eax,%r13d
  4012d6:	eb 2b                	jmp    401303 <main+0x14e>
  4012d8:	c7 05 c6 41 20 00 00 	movl   $0x0,0x2041c6(%rip)        # 6054a8 <notify>
  4012df:	00 00 00 
  4012e2:	eb 1f                	jmp    401303 <main+0x14e>
  4012e4:	0f be d2             	movsbl %dl,%edx
  4012e7:	be 6f 31 40 00       	mov    $0x40316f,%esi
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
  40131b:	be 01 00 00 00       	mov    $0x1,%esi
  401320:	44 89 ef             	mov    %r13d,%edi
  401323:	e8 08 fd ff ff       	callq  401030 <initialize_target>
  401328:	83 3d f9 41 20 00 00 	cmpl   $0x0,0x2041f9(%rip)        # 605528 <is_checker>
  40132f:	74 2a                	je     40135b <main+0x1a6>
  401331:	44 3b 35 e8 41 20 00 	cmp    0x2041e8(%rip),%r14d        # 605520 <authkey>
  401338:	74 21                	je     40135b <main+0x1a6>
  40133a:	44 89 f2             	mov    %r14d,%edx
  40133d:	be a8 30 40 00       	mov    $0x4030a8,%esi
  401342:	bf 01 00 00 00       	mov    $0x1,%edi
  401347:	b8 00 00 00 00       	mov    $0x0,%eax
  40134c:	e8 af fa ff ff       	callq  400e00 <__printf_chk@plt>
  401351:	b8 00 00 00 00       	mov    $0x0,%eax
  401356:	e8 0b 08 00 00       	callq  401b66 <check_fail>
  40135b:	8b 15 c3 41 20 00    	mov    0x2041c3(%rip),%edx        # 605524 <cookie>
  401361:	be 82 31 40 00       	mov    $0x403182,%esi
  401366:	bf 01 00 00 00       	mov    $0x1,%edi
  40136b:	b8 00 00 00 00       	mov    $0x0,%eax
  401370:	e8 8b fa ff ff       	callq  400e00 <__printf_chk@plt>
  401375:	48 8b 3d 24 41 20 00 	mov    0x204124(%rip),%rdi        # 6054a0 <buf_offset>
  40137c:	e8 86 0c 00 00       	callq  402007 <launch>
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
  4017f6:	e8 a0 03 00 00       	callq  401b9b <Gets>
  4017fb:	b8 01 00 00 00       	mov    $0x1,%eax
  401800:	48 83 c4 38          	add    $0x38,%rsp
  401804:	c3                   	retq   

0000000000401805 <touch1>:
  401805:	48 83 ec 08          	sub    $0x8,%rsp
  401809:	c7 05 09 3d 20 00 01 	movl   $0x1,0x203d09(%rip)        # 60551c <vlevel>
  401810:	00 00 00 
  401813:	bf 65 32 40 00       	mov    $0x403265,%edi
  401818:	e8 b3 f4 ff ff       	callq  400cd0 <puts@plt>
  40181d:	bf 01 00 00 00       	mov    $0x1,%edi
  401822:	e8 b9 05 00 00       	callq  401de0 <validate>
  401827:	bf 00 00 00 00       	mov    $0x0,%edi
  40182c:	e8 1f f6 ff ff       	callq  400e50 <exit@plt>

0000000000401831 <touch2>:
  401831:	48 83 ec 08          	sub    $0x8,%rsp
  401835:	89 fa                	mov    %edi,%edx
  401837:	c7 05 db 3c 20 00 02 	movl   $0x2,0x203cdb(%rip)        # 60551c <vlevel>
  40183e:	00 00 00 
  401841:	39 3d dd 3c 20 00    	cmp    %edi,0x203cdd(%rip)        # 605524 <cookie>
  401847:	75 20                	jne    401869 <touch2+0x38>
  401849:	be 88 32 40 00       	mov    $0x403288,%esi
  40184e:	bf 01 00 00 00       	mov    $0x1,%edi
  401853:	b8 00 00 00 00       	mov    $0x0,%eax
  401858:	e8 a3 f5 ff ff       	callq  400e00 <__printf_chk@plt>
  40185d:	bf 02 00 00 00       	mov    $0x2,%edi
  401862:	e8 79 05 00 00       	callq  401de0 <validate>
  401867:	eb 1e                	jmp    401887 <touch2+0x56>
  401869:	be b0 32 40 00       	mov    $0x4032b0,%esi
  40186e:	bf 01 00 00 00       	mov    $0x1,%edi
  401873:	b8 00 00 00 00       	mov    $0x0,%eax
  401878:	e8 83 f5 ff ff       	callq  400e00 <__printf_chk@plt>
  40187d:	bf 02 00 00 00       	mov    $0x2,%edi
  401882:	e8 1b 06 00 00       	callq  401ea2 <fail>
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
  4018ee:	b9 82 32 40 00       	mov    $0x403282,%ecx
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
  401946:	c7 05 cc 3b 20 00 03 	movl   $0x3,0x203bcc(%rip)        # 60551c <vlevel>
  40194d:	00 00 00 
  401950:	48 89 fe             	mov    %rdi,%rsi
  401953:	8b 3d cb 3b 20 00    	mov    0x203bcb(%rip),%edi        # 605524 <cookie>
  401959:	e8 33 ff ff ff       	callq  401891 <hexmatch>
  40195e:	85 c0                	test   %eax,%eax
  401960:	74 23                	je     401985 <touch3+0x43>
  401962:	48 89 da             	mov    %rbx,%rdx
  401965:	be d8 32 40 00       	mov    $0x4032d8,%esi
  40196a:	bf 01 00 00 00       	mov    $0x1,%edi
  40196f:	b8 00 00 00 00       	mov    $0x0,%eax
  401974:	e8 87 f4 ff ff       	callq  400e00 <__printf_chk@plt>
  401979:	bf 03 00 00 00       	mov    $0x3,%edi
  40197e:	e8 5d 04 00 00       	callq  401de0 <validate>
  401983:	eb 21                	jmp    4019a6 <touch3+0x64>
  401985:	48 89 da             	mov    %rbx,%rdx
  401988:	be 00 33 40 00       	mov    $0x403300,%esi
  40198d:	bf 01 00 00 00       	mov    $0x1,%edi
  401992:	b8 00 00 00 00       	mov    $0x0,%eax
  401997:	e8 64 f4 ff ff       	callq  400e00 <__printf_chk@plt>
  40199c:	bf 03 00 00 00       	mov    $0x3,%edi
  4019a1:	e8 fc 04 00 00       	callq  401ea2 <fail>
  4019a6:	bf 00 00 00 00       	mov    $0x0,%edi
  4019ab:	e8 a0 f4 ff ff       	callq  400e50 <exit@plt>

00000000004019b0 <test>:
  4019b0:	48 83 ec 08          	sub    $0x8,%rsp
  4019b4:	b8 00 00 00 00       	mov    $0x0,%eax
  4019b9:	e8 31 fe ff ff       	callq  4017ef <getbuf>
  4019be:	89 c2                	mov    %eax,%edx
  4019c0:	be 28 33 40 00       	mov    $0x403328,%esi
  4019c5:	bf 01 00 00 00       	mov    $0x1,%edi
  4019ca:	b8 00 00 00 00       	mov    $0x0,%eax
  4019cf:	e8 2c f4 ff ff       	callq  400e00 <__printf_chk@plt>
  4019d4:	48 83 c4 08          	add    $0x8,%rsp
  4019d8:	c3                   	retq   

00000000004019d9 <start_farm>:
  4019d9:	b8 01 00 00 00       	mov    $0x1,%eax
  4019de:	c3                   	retq   

00000000004019df <addval_460>:
  4019df:	8d 87 58 c1 e3 12    	lea    0x12e3c158(%rdi),%eax
  4019e5:	c3                   	retq   

00000000004019e6 <getval_436>:
  4019e6:	b8 6c 4c 58 92       	mov    $0x92584c6c,%eax
  4019eb:	c3                   	retq   

00000000004019ec <setval_111>:
  4019ec:	c7 07 58 90 c3 f4    	movl   $0xf4c39058,(%rdi)
  4019f2:	c3                   	retq   

00000000004019f3 <getval_429>:
  4019f3:	b8 40 89 c7 c3       	mov    $0xc3c78940,%eax
  4019f8:	c3                   	retq   

00000000004019f9 <addval_137>:
  4019f9:	8d 87 62 48 89 c7    	lea    -0x3876b79e(%rdi),%eax
  4019ff:	c3                   	retq   

0000000000401a00 <setval_183>:
  401a00:	c7 07 bd 48 89 c7    	movl   $0xc78948bd,(%rdi)
  401a06:	c3                   	retq   

0000000000401a07 <setval_447>:
  401a07:	c7 07 ed 9c 58 c3    	movl   $0xc3589ced,(%rdi)
  401a0d:	c3                   	retq   

0000000000401a0e <addval_100>:
  401a0e:	8d 87 48 89 c7 c1    	lea    -0x3e3876b8(%rdi),%eax
  401a14:	c3                   	retq   

0000000000401a15 <mid_farm>:
  401a15:	b8 01 00 00 00       	mov    $0x1,%eax
  401a1a:	c3                   	retq   

0000000000401a1b <add_xy>:
  401a1b:	48 8d 04 37          	lea    (%rdi,%rsi,1),%rax
  401a1f:	c3                   	retq   

0000000000401a20 <addval_194>:
  401a20:	8d 87 89 ca 60 db    	lea    -0x249f3577(%rdi),%eax
  401a26:	c3                   	retq   

0000000000401a27 <getval_219>:
  401a27:	b8 4c 89 e0 c3       	mov    $0xc3e0894c,%eax
  401a2c:	c3                   	retq   

0000000000401a2d <setval_307>:
  401a2d:	c7 07 6d 89 d6 90    	movl   $0x90d6896d,(%rdi)
  401a33:	c3                   	retq   

0000000000401a34 <setval_310>:
  401a34:	c7 07 48 89 e0 c3    	movl   $0xc3e08948,(%rdi)
  401a3a:	c3                   	retq   

0000000000401a3b <addval_273>:
  401a3b:	8d 87 89 c1 84 db    	lea    -0x247b3e77(%rdi),%eax
  401a41:	c3                   	retq   

0000000000401a42 <getval_416>:
  401a42:	b8 89 d6 28 c0       	mov    $0xc028d689,%eax
  401a47:	c3                   	retq   

0000000000401a48 <addval_115>:
  401a48:	8d 87 48 89 e0 91    	lea    -0x6e1f76b8(%rdi),%eax
  401a4e:	c3                   	retq   

0000000000401a4f <getval_126>:
  401a4f:	b8 56 89 d6 c3       	mov    $0xc3d68956,%eax
  401a54:	c3                   	retq   

0000000000401a55 <addval_394>:
  401a55:	8d 87 99 ca 84 c9    	lea    -0x367b3567(%rdi),%eax
  401a5b:	c3                   	retq   

0000000000401a5c <setval_319>:
  401a5c:	c7 07 89 ca 20 d2    	movl   $0xd220ca89,(%rdi)
  401a62:	c3                   	retq   

0000000000401a63 <setval_181>:
  401a63:	c7 07 a9 ca 84 c0    	movl   $0xc084caa9,(%rdi)
  401a69:	c3                   	retq   

0000000000401a6a <setval_226>:
  401a6a:	c7 07 09 c1 84 c9    	movl   $0xc984c109,(%rdi)
  401a70:	c3                   	retq   

0000000000401a71 <getval_112>:
  401a71:	b8 81 c1 08 db       	mov    $0xdb08c181,%eax
  401a76:	c3                   	retq   

0000000000401a77 <addval_433>:
  401a77:	8d 87 48 89 e0 c3    	lea    -0x3c1f76b8(%rdi),%eax
  401a7d:	c3                   	retq   

0000000000401a7e <getval_390>:
  401a7e:	b8 89 ca 00 db       	mov    $0xdb00ca89,%eax
  401a83:	c3                   	retq   

0000000000401a84 <setval_437>:
  401a84:	c7 07 a9 d6 90 90    	movl   $0x9090d6a9,(%rdi)
  401a8a:	c3                   	retq   

0000000000401a8b <getval_167>:
  401a8b:	b8 89 c1 c2 df       	mov    $0xdfc2c189,%eax
  401a90:	c3                   	retq   

0000000000401a91 <setval_275>:
  401a91:	c7 07 21 4a 89 e0    	movl   $0xe0894a21,(%rdi)
  401a97:	c3                   	retq   

0000000000401a98 <setval_142>:
  401a98:	c7 07 76 99 d6 90    	movl   $0x90d69976,(%rdi)
  401a9e:	c3                   	retq   

0000000000401a9f <addval_109>:
  401a9f:	8d 87 89 ca 18 c0    	lea    -0x3fe73577(%rdi),%eax
  401aa5:	c3                   	retq   

0000000000401aa6 <setval_379>:
  401aa6:	c7 07 09 ca 08 c9    	movl   $0xc908ca09,(%rdi)
  401aac:	c3                   	retq   

0000000000401aad <addval_236>:
  401aad:	8d 87 49 89 e0 c3    	lea    -0x3c1f76b7(%rdi),%eax
  401ab3:	c3                   	retq   

0000000000401ab4 <addval_106>:
  401ab4:	8d 87 89 d6 60 c0    	lea    -0x3f9f2977(%rdi),%eax
  401aba:	c3                   	retq   

0000000000401abb <addval_374>:
  401abb:	8d 87 d7 a9 c1 c3    	lea    -0x3c3e5629(%rdi),%eax
  401ac1:	c3                   	retq   

0000000000401ac2 <getval_322>:
  401ac2:	b8 89 ca 20 c0       	mov    $0xc020ca89,%eax
  401ac7:	c3                   	retq   

0000000000401ac8 <getval_149>:
  401ac8:	b8 09 c1 90 c3       	mov    $0xc390c109,%eax
  401acd:	c3                   	retq   

0000000000401ace <setval_117>:
  401ace:	c7 07 8d d6 38 c9    	movl   $0xc938d68d,(%rdi)
  401ad4:	c3                   	retq   

0000000000401ad5 <getval_361>:
  401ad5:	b8 89 c1 94 90       	mov    $0x9094c189,%eax
  401ada:	c3                   	retq   

0000000000401adb <setval_119>:
  401adb:	c7 07 89 c1 08 db    	movl   $0xdb08c189,(%rdi)
  401ae1:	c3                   	retq   

0000000000401ae2 <getval_184>:
  401ae2:	b8 48 a9 e0 c3       	mov    $0xc3e0a948,%eax
  401ae7:	c3                   	retq   

0000000000401ae8 <setval_287>:
  401ae8:	c7 07 48 a9 e0 c3    	movl   $0xc3e0a948,(%rdi)
  401aee:	c3                   	retq   

0000000000401aef <getval_172>:
  401aef:	b8 89 d6 a4 c9       	mov    $0xc9a4d689,%eax
  401af4:	c3                   	retq   

0000000000401af5 <end_farm>:
  401af5:	b8 01 00 00 00       	mov    $0x1,%eax
  401afa:	c3                   	retq   

0000000000401afb <save_char>:
  401afb:	8b 05 43 46 20 00    	mov    0x204643(%rip),%eax        # 606144 <gets_cnt>
  401b01:	3d ff 03 00 00       	cmp    $0x3ff,%eax
  401b06:	7f 49                	jg     401b51 <save_char+0x56>
  401b08:	8d 14 40             	lea    (%rax,%rax,2),%edx
  401b0b:	89 f9                	mov    %edi,%ecx
  401b0d:	c0 e9 04             	shr    $0x4,%cl
  401b10:	83 e1 0f             	and    $0xf,%ecx
  401b13:	0f b6 b1 50 36 40 00 	movzbl 0x403650(%rcx),%esi
  401b1a:	48 63 ca             	movslq %edx,%rcx
  401b1d:	40 88 b1 40 55 60 00 	mov    %sil,0x605540(%rcx)
  401b24:	8d 4a 01             	lea    0x1(%rdx),%ecx
  401b27:	83 e7 0f             	and    $0xf,%edi
  401b2a:	0f b6 b7 50 36 40 00 	movzbl 0x403650(%rdi),%esi
  401b31:	48 63 c9             	movslq %ecx,%rcx
  401b34:	40 88 b1 40 55 60 00 	mov    %sil,0x605540(%rcx)
  401b3b:	83 c2 02             	add    $0x2,%edx
  401b3e:	48 63 d2             	movslq %edx,%rdx
  401b41:	c6 82 40 55 60 00 20 	movb   $0x20,0x605540(%rdx)
  401b48:	83 c0 01             	add    $0x1,%eax
  401b4b:	89 05 f3 45 20 00    	mov    %eax,0x2045f3(%rip)        # 606144 <gets_cnt>
  401b51:	f3 c3                	repz retq 

0000000000401b53 <save_term>:
  401b53:	8b 05 eb 45 20 00    	mov    0x2045eb(%rip),%eax        # 606144 <gets_cnt>
  401b59:	8d 04 40             	lea    (%rax,%rax,2),%eax
  401b5c:	48 98                	cltq   
  401b5e:	c6 80 40 55 60 00 00 	movb   $0x0,0x605540(%rax)
  401b65:	c3                   	retq   

0000000000401b66 <check_fail>:
  401b66:	48 83 ec 08          	sub    $0x8,%rsp
  401b6a:	0f be 15 d7 45 20 00 	movsbl 0x2045d7(%rip),%edx        # 606148 <target_prefix>
  401b71:	41 b8 40 55 60 00    	mov    $0x605540,%r8d
  401b77:	8b 0d 9b 39 20 00    	mov    0x20399b(%rip),%ecx        # 605518 <check_level>
  401b7d:	be 4b 33 40 00       	mov    $0x40334b,%esi
  401b82:	bf 01 00 00 00       	mov    $0x1,%edi
  401b87:	b8 00 00 00 00       	mov    $0x0,%eax
  401b8c:	e8 6f f2 ff ff       	callq  400e00 <__printf_chk@plt>
  401b91:	bf 01 00 00 00       	mov    $0x1,%edi
  401b96:	e8 b5 f2 ff ff       	callq  400e50 <exit@plt>

0000000000401b9b <Gets>:
  401b9b:	41 54                	push   %r12
  401b9d:	55                   	push   %rbp
  401b9e:	53                   	push   %rbx
  401b9f:	49 89 fc             	mov    %rdi,%r12
  401ba2:	c7 05 98 45 20 00 00 	movl   $0x0,0x204598(%rip)        # 606144 <gets_cnt>
  401ba9:	00 00 00 
  401bac:	48 89 fb             	mov    %rdi,%rbx
  401baf:	eb 11                	jmp    401bc2 <Gets+0x27>
  401bb1:	48 8d 6b 01          	lea    0x1(%rbx),%rbp
  401bb5:	88 03                	mov    %al,(%rbx)
  401bb7:	0f b6 f8             	movzbl %al,%edi
  401bba:	e8 3c ff ff ff       	callq  401afb <save_char>
  401bbf:	48 89 eb             	mov    %rbp,%rbx
  401bc2:	48 8b 3d 47 39 20 00 	mov    0x203947(%rip),%rdi        # 605510 <infile>
  401bc9:	e8 02 f2 ff ff       	callq  400dd0 <_IO_getc@plt>
  401bce:	83 f8 ff             	cmp    $0xffffffff,%eax
  401bd1:	74 05                	je     401bd8 <Gets+0x3d>
  401bd3:	83 f8 0a             	cmp    $0xa,%eax
  401bd6:	75 d9                	jne    401bb1 <Gets+0x16>
  401bd8:	c6 03 00             	movb   $0x0,(%rbx)
  401bdb:	b8 00 00 00 00       	mov    $0x0,%eax
  401be0:	e8 6e ff ff ff       	callq  401b53 <save_term>
  401be5:	4c 89 e0             	mov    %r12,%rax
  401be8:	5b                   	pop    %rbx
  401be9:	5d                   	pop    %rbp
  401bea:	41 5c                	pop    %r12
  401bec:	c3                   	retq   

0000000000401bed <notify_server>:
  401bed:	53                   	push   %rbx
  401bee:	48 81 ec 10 40 00 00 	sub    $0x4010,%rsp
  401bf5:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401bfc:	00 00 
  401bfe:	48 89 84 24 08 40 00 	mov    %rax,0x4008(%rsp)
  401c05:	00 
  401c06:	31 c0                	xor    %eax,%eax
  401c08:	83 3d 19 39 20 00 00 	cmpl   $0x0,0x203919(%rip)        # 605528 <is_checker>
  401c0f:	0f 85 aa 01 00 00    	jne    401dbf <notify_server+0x1d2>
  401c15:	89 fb                	mov    %edi,%ebx
  401c17:	8b 05 27 45 20 00    	mov    0x204527(%rip),%eax        # 606144 <gets_cnt>
  401c1d:	83 c0 64             	add    $0x64,%eax
  401c20:	3d 00 20 00 00       	cmp    $0x2000,%eax
  401c25:	7e 1e                	jle    401c45 <notify_server+0x58>
  401c27:	be 80 34 40 00       	mov    $0x403480,%esi
  401c2c:	bf 01 00 00 00       	mov    $0x1,%edi
  401c31:	b8 00 00 00 00       	mov    $0x0,%eax
  401c36:	e8 c5 f1 ff ff       	callq  400e00 <__printf_chk@plt>
  401c3b:	bf 01 00 00 00       	mov    $0x1,%edi
  401c40:	e8 0b f2 ff ff       	callq  400e50 <exit@plt>
  401c45:	0f be 05 fc 44 20 00 	movsbl 0x2044fc(%rip),%eax        # 606148 <target_prefix>
  401c4c:	83 3d 55 38 20 00 00 	cmpl   $0x0,0x203855(%rip)        # 6054a8 <notify>
  401c53:	74 08                	je     401c5d <notify_server+0x70>
  401c55:	8b 15 c5 38 20 00    	mov    0x2038c5(%rip),%edx        # 605520 <authkey>
  401c5b:	eb 05                	jmp    401c62 <notify_server+0x75>
  401c5d:	ba ff ff ff ff       	mov    $0xffffffff,%edx
  401c62:	85 db                	test   %ebx,%ebx
  401c64:	74 08                	je     401c6e <notify_server+0x81>
  401c66:	41 b9 61 33 40 00    	mov    $0x403361,%r9d
  401c6c:	eb 06                	jmp    401c74 <notify_server+0x87>
  401c6e:	41 b9 66 33 40 00    	mov    $0x403366,%r9d
  401c74:	68 40 55 60 00       	pushq  $0x605540
  401c79:	56                   	push   %rsi
  401c7a:	50                   	push   %rax
  401c7b:	52                   	push   %rdx
  401c7c:	44 8b 05 e5 34 20 00 	mov    0x2034e5(%rip),%r8d        # 605168 <target_id>
  401c83:	b9 6b 33 40 00       	mov    $0x40336b,%ecx
  401c88:	ba 00 20 00 00       	mov    $0x2000,%edx
  401c8d:	be 01 00 00 00       	mov    $0x1,%esi
  401c92:	48 8d 7c 24 20       	lea    0x20(%rsp),%rdi
  401c97:	b8 00 00 00 00       	mov    $0x0,%eax
  401c9c:	e8 df f1 ff ff       	callq  400e80 <__sprintf_chk@plt>
  401ca1:	48 83 c4 20          	add    $0x20,%rsp
  401ca5:	83 3d fc 37 20 00 00 	cmpl   $0x0,0x2037fc(%rip)        # 6054a8 <notify>
  401cac:	0f 84 81 00 00 00    	je     401d33 <notify_server+0x146>
  401cb2:	85 db                	test   %ebx,%ebx
  401cb4:	74 6e                	je     401d24 <notify_server+0x137>
  401cb6:	4c 8d 8c 24 00 20 00 	lea    0x2000(%rsp),%r9
  401cbd:	00 
  401cbe:	41 b8 00 00 00 00    	mov    $0x0,%r8d
  401cc4:	48 89 e1             	mov    %rsp,%rcx
  401cc7:	48 8b 15 a2 34 20 00 	mov    0x2034a2(%rip),%rdx        # 605170 <lab>
  401cce:	48 8b 35 a3 34 20 00 	mov    0x2034a3(%rip),%rsi        # 605178 <course>
  401cd5:	48 8b 3d 84 34 20 00 	mov    0x203484(%rip),%rdi        # 605160 <user_id>
  401cdc:	e8 ef 10 00 00       	callq  402dd0 <driver_post>
  401ce1:	85 c0                	test   %eax,%eax
  401ce3:	79 26                	jns    401d0b <notify_server+0x11e>
  401ce5:	48 8d 94 24 00 20 00 	lea    0x2000(%rsp),%rdx
  401cec:	00 
  401ced:	be 87 33 40 00       	mov    $0x403387,%esi
  401cf2:	bf 01 00 00 00       	mov    $0x1,%edi
  401cf7:	b8 00 00 00 00       	mov    $0x0,%eax
  401cfc:	e8 ff f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401d01:	bf 01 00 00 00       	mov    $0x1,%edi
  401d06:	e8 45 f1 ff ff       	callq  400e50 <exit@plt>
  401d0b:	bf b0 34 40 00       	mov    $0x4034b0,%edi
  401d10:	e8 bb ef ff ff       	callq  400cd0 <puts@plt>
  401d15:	bf 93 33 40 00       	mov    $0x403393,%edi
  401d1a:	e8 b1 ef ff ff       	callq  400cd0 <puts@plt>
  401d1f:	e9 9b 00 00 00       	jmpq   401dbf <notify_server+0x1d2>
  401d24:	bf 9d 33 40 00       	mov    $0x40339d,%edi
  401d29:	e8 a2 ef ff ff       	callq  400cd0 <puts@plt>
  401d2e:	e9 8c 00 00 00       	jmpq   401dbf <notify_server+0x1d2>
  401d33:	85 db                	test   %ebx,%ebx
  401d35:	74 07                	je     401d3e <notify_server+0x151>
  401d37:	ba 61 33 40 00       	mov    $0x403361,%edx
  401d3c:	eb 05                	jmp    401d43 <notify_server+0x156>
  401d3e:	ba 66 33 40 00       	mov    $0x403366,%edx
  401d43:	be e8 34 40 00       	mov    $0x4034e8,%esi
  401d48:	bf 01 00 00 00       	mov    $0x1,%edi
  401d4d:	b8 00 00 00 00       	mov    $0x0,%eax
  401d52:	e8 a9 f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401d57:	48 8b 15 02 34 20 00 	mov    0x203402(%rip),%rdx        # 605160 <user_id>
  401d5e:	be a4 33 40 00       	mov    $0x4033a4,%esi
  401d63:	bf 01 00 00 00       	mov    $0x1,%edi
  401d68:	b8 00 00 00 00       	mov    $0x0,%eax
  401d6d:	e8 8e f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401d72:	48 8b 15 ff 33 20 00 	mov    0x2033ff(%rip),%rdx        # 605178 <course>
  401d79:	be b1 33 40 00       	mov    $0x4033b1,%esi
  401d7e:	bf 01 00 00 00       	mov    $0x1,%edi
  401d83:	b8 00 00 00 00       	mov    $0x0,%eax
  401d88:	e8 73 f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401d8d:	48 8b 15 dc 33 20 00 	mov    0x2033dc(%rip),%rdx        # 605170 <lab>
  401d94:	be bd 33 40 00       	mov    $0x4033bd,%esi
  401d99:	bf 01 00 00 00       	mov    $0x1,%edi
  401d9e:	b8 00 00 00 00       	mov    $0x0,%eax
  401da3:	e8 58 f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401da8:	48 89 e2             	mov    %rsp,%rdx
  401dab:	be c6 33 40 00       	mov    $0x4033c6,%esi
  401db0:	bf 01 00 00 00       	mov    $0x1,%edi
  401db5:	b8 00 00 00 00       	mov    $0x0,%eax
  401dba:	e8 41 f0 ff ff       	callq  400e00 <__printf_chk@plt>
  401dbf:	48 8b 84 24 08 40 00 	mov    0x4008(%rsp),%rax
  401dc6:	00 
  401dc7:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  401dce:	00 00 
  401dd0:	74 05                	je     401dd7 <notify_server+0x1ea>
  401dd2:	e8 19 ef ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  401dd7:	48 81 c4 10 40 00 00 	add    $0x4010,%rsp
  401dde:	5b                   	pop    %rbx
  401ddf:	c3                   	retq   

0000000000401de0 <validate>:
  401de0:	53                   	push   %rbx
  401de1:	89 fb                	mov    %edi,%ebx
  401de3:	83 3d 3e 37 20 00 00 	cmpl   $0x0,0x20373e(%rip)        # 605528 <is_checker>
  401dea:	74 6b                	je     401e57 <validate+0x77>
  401dec:	39 3d 2a 37 20 00    	cmp    %edi,0x20372a(%rip)        # 60551c <vlevel>
  401df2:	74 14                	je     401e08 <validate+0x28>
  401df4:	bf d2 33 40 00       	mov    $0x4033d2,%edi
  401df9:	e8 d2 ee ff ff       	callq  400cd0 <puts@plt>
  401dfe:	b8 00 00 00 00       	mov    $0x0,%eax
  401e03:	e8 5e fd ff ff       	callq  401b66 <check_fail>
  401e08:	8b 15 0a 37 20 00    	mov    0x20370a(%rip),%edx        # 605518 <check_level>
  401e0e:	39 d7                	cmp    %edx,%edi
  401e10:	74 20                	je     401e32 <validate+0x52>
  401e12:	89 f9                	mov    %edi,%ecx
  401e14:	be 10 35 40 00       	mov    $0x403510,%esi
  401e19:	bf 01 00 00 00       	mov    $0x1,%edi
  401e1e:	b8 00 00 00 00       	mov    $0x0,%eax
  401e23:	e8 d8 ef ff ff       	callq  400e00 <__printf_chk@plt>
  401e28:	b8 00 00 00 00       	mov    $0x0,%eax
  401e2d:	e8 34 fd ff ff       	callq  401b66 <check_fail>
  401e32:	0f be 15 0f 43 20 00 	movsbl 0x20430f(%rip),%edx        # 606148 <target_prefix>
  401e39:	41 b8 40 55 60 00    	mov    $0x605540,%r8d
  401e3f:	89 f9                	mov    %edi,%ecx
  401e41:	be f0 33 40 00       	mov    $0x4033f0,%esi
  401e46:	bf 01 00 00 00       	mov    $0x1,%edi
  401e4b:	b8 00 00 00 00       	mov    $0x0,%eax
  401e50:	e8 ab ef ff ff       	callq  400e00 <__printf_chk@plt>
  401e55:	eb 49                	jmp    401ea0 <validate+0xc0>
  401e57:	3b 3d bf 36 20 00    	cmp    0x2036bf(%rip),%edi        # 60551c <vlevel>
  401e5d:	74 18                	je     401e77 <validate+0x97>
  401e5f:	bf d2 33 40 00       	mov    $0x4033d2,%edi
  401e64:	e8 67 ee ff ff       	callq  400cd0 <puts@plt>
  401e69:	89 de                	mov    %ebx,%esi
  401e6b:	bf 00 00 00 00       	mov    $0x0,%edi
  401e70:	e8 78 fd ff ff       	callq  401bed <notify_server>
  401e75:	eb 29                	jmp    401ea0 <validate+0xc0>
  401e77:	0f be 0d ca 42 20 00 	movsbl 0x2042ca(%rip),%ecx        # 606148 <target_prefix>
  401e7e:	89 fa                	mov    %edi,%edx
  401e80:	be 38 35 40 00       	mov    $0x403538,%esi
  401e85:	bf 01 00 00 00       	mov    $0x1,%edi
  401e8a:	b8 00 00 00 00       	mov    $0x0,%eax
  401e8f:	e8 6c ef ff ff       	callq  400e00 <__printf_chk@plt>
  401e94:	89 de                	mov    %ebx,%esi
  401e96:	bf 01 00 00 00       	mov    $0x1,%edi
  401e9b:	e8 4d fd ff ff       	callq  401bed <notify_server>
  401ea0:	5b                   	pop    %rbx
  401ea1:	c3                   	retq   

0000000000401ea2 <fail>:
  401ea2:	48 83 ec 08          	sub    $0x8,%rsp
  401ea6:	83 3d 7b 36 20 00 00 	cmpl   $0x0,0x20367b(%rip)        # 605528 <is_checker>
  401ead:	74 0a                	je     401eb9 <fail+0x17>
  401eaf:	b8 00 00 00 00       	mov    $0x0,%eax
  401eb4:	e8 ad fc ff ff       	callq  401b66 <check_fail>
  401eb9:	89 fe                	mov    %edi,%esi
  401ebb:	bf 00 00 00 00       	mov    $0x0,%edi
  401ec0:	e8 28 fd ff ff       	callq  401bed <notify_server>
  401ec5:	48 83 c4 08          	add    $0x8,%rsp
  401ec9:	c3                   	retq   

0000000000401eca <bushandler>:
  401eca:	48 83 ec 08          	sub    $0x8,%rsp
  401ece:	83 3d 53 36 20 00 00 	cmpl   $0x0,0x203653(%rip)        # 605528 <is_checker>
  401ed5:	74 14                	je     401eeb <bushandler+0x21>
  401ed7:	bf 05 34 40 00       	mov    $0x403405,%edi
  401edc:	e8 ef ed ff ff       	callq  400cd0 <puts@plt>
  401ee1:	b8 00 00 00 00       	mov    $0x0,%eax
  401ee6:	e8 7b fc ff ff       	callq  401b66 <check_fail>
  401eeb:	bf 70 35 40 00       	mov    $0x403570,%edi
  401ef0:	e8 db ed ff ff       	callq  400cd0 <puts@plt>
  401ef5:	bf 0f 34 40 00       	mov    $0x40340f,%edi
  401efa:	e8 d1 ed ff ff       	callq  400cd0 <puts@plt>
  401eff:	be 00 00 00 00       	mov    $0x0,%esi
  401f04:	bf 00 00 00 00       	mov    $0x0,%edi
  401f09:	e8 df fc ff ff       	callq  401bed <notify_server>
  401f0e:	bf 01 00 00 00       	mov    $0x1,%edi
  401f13:	e8 38 ef ff ff       	callq  400e50 <exit@plt>

0000000000401f18 <seghandler>:
  401f18:	48 83 ec 08          	sub    $0x8,%rsp
  401f1c:	83 3d 05 36 20 00 00 	cmpl   $0x0,0x203605(%rip)        # 605528 <is_checker>
  401f23:	74 14                	je     401f39 <seghandler+0x21>
  401f25:	bf 25 34 40 00       	mov    $0x403425,%edi
  401f2a:	e8 a1 ed ff ff       	callq  400cd0 <puts@plt>
  401f2f:	b8 00 00 00 00       	mov    $0x0,%eax
  401f34:	e8 2d fc ff ff       	callq  401b66 <check_fail>
  401f39:	bf 90 35 40 00       	mov    $0x403590,%edi
  401f3e:	e8 8d ed ff ff       	callq  400cd0 <puts@plt>
  401f43:	bf 0f 34 40 00       	mov    $0x40340f,%edi
  401f48:	e8 83 ed ff ff       	callq  400cd0 <puts@plt>
  401f4d:	be 00 00 00 00       	mov    $0x0,%esi
  401f52:	bf 00 00 00 00       	mov    $0x0,%edi
  401f57:	e8 91 fc ff ff       	callq  401bed <notify_server>
  401f5c:	bf 01 00 00 00       	mov    $0x1,%edi
  401f61:	e8 ea ee ff ff       	callq  400e50 <exit@plt>

0000000000401f66 <illegalhandler>:
  401f66:	48 83 ec 08          	sub    $0x8,%rsp
  401f6a:	83 3d b7 35 20 00 00 	cmpl   $0x0,0x2035b7(%rip)        # 605528 <is_checker>
  401f71:	74 14                	je     401f87 <illegalhandler+0x21>
  401f73:	bf 38 34 40 00       	mov    $0x403438,%edi
  401f78:	e8 53 ed ff ff       	callq  400cd0 <puts@plt>
  401f7d:	b8 00 00 00 00       	mov    $0x0,%eax
  401f82:	e8 df fb ff ff       	callq  401b66 <check_fail>
  401f87:	bf b8 35 40 00       	mov    $0x4035b8,%edi
  401f8c:	e8 3f ed ff ff       	callq  400cd0 <puts@plt>
  401f91:	bf 0f 34 40 00       	mov    $0x40340f,%edi
  401f96:	e8 35 ed ff ff       	callq  400cd0 <puts@plt>
  401f9b:	be 00 00 00 00       	mov    $0x0,%esi
  401fa0:	bf 00 00 00 00       	mov    $0x0,%edi
  401fa5:	e8 43 fc ff ff       	callq  401bed <notify_server>
  401faa:	bf 01 00 00 00       	mov    $0x1,%edi
  401faf:	e8 9c ee ff ff       	callq  400e50 <exit@plt>

0000000000401fb4 <sigalrmhandler>:
  401fb4:	48 83 ec 08          	sub    $0x8,%rsp
  401fb8:	83 3d 69 35 20 00 00 	cmpl   $0x0,0x203569(%rip)        # 605528 <is_checker>
  401fbf:	74 14                	je     401fd5 <sigalrmhandler+0x21>
  401fc1:	bf 4c 34 40 00       	mov    $0x40344c,%edi
  401fc6:	e8 05 ed ff ff       	callq  400cd0 <puts@plt>
  401fcb:	b8 00 00 00 00       	mov    $0x0,%eax
  401fd0:	e8 91 fb ff ff       	callq  401b66 <check_fail>
  401fd5:	ba 05 00 00 00       	mov    $0x5,%edx
  401fda:	be e8 35 40 00       	mov    $0x4035e8,%esi
  401fdf:	bf 01 00 00 00       	mov    $0x1,%edi
  401fe4:	b8 00 00 00 00       	mov    $0x0,%eax
  401fe9:	e8 12 ee ff ff       	callq  400e00 <__printf_chk@plt>
  401fee:	be 00 00 00 00       	mov    $0x0,%esi
  401ff3:	bf 00 00 00 00       	mov    $0x0,%edi
  401ff8:	e8 f0 fb ff ff       	callq  401bed <notify_server>
  401ffd:	bf 01 00 00 00       	mov    $0x1,%edi
  402002:	e8 49 ee ff ff       	callq  400e50 <exit@plt>

0000000000402007 <launch>:
  402007:	55                   	push   %rbp
  402008:	48 89 e5             	mov    %rsp,%rbp
  40200b:	48 83 ec 10          	sub    $0x10,%rsp
  40200f:	48 89 fa             	mov    %rdi,%rdx
  402012:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  402019:	00 00 
  40201b:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  40201f:	31 c0                	xor    %eax,%eax
  402021:	48 8d 47 1e          	lea    0x1e(%rdi),%rax
  402025:	48 83 e0 f0          	and    $0xfffffffffffffff0,%rax
  402029:	48 29 c4             	sub    %rax,%rsp
  40202c:	48 8d 7c 24 0f       	lea    0xf(%rsp),%rdi
  402031:	48 83 e7 f0          	and    $0xfffffffffffffff0,%rdi
  402035:	be f4 00 00 00       	mov    $0xf4,%esi
  40203a:	e8 d1 ec ff ff       	callq  400d10 <memset@plt>
  40203f:	48 8b 05 7a 34 20 00 	mov    0x20347a(%rip),%rax        # 6054c0 <stdin@@GLIBC_2.2.5>
  402046:	48 39 05 c3 34 20 00 	cmp    %rax,0x2034c3(%rip)        # 605510 <infile>
  40204d:	75 14                	jne    402063 <launch+0x5c>
  40204f:	be 54 34 40 00       	mov    $0x403454,%esi
  402054:	bf 01 00 00 00       	mov    $0x1,%edi
  402059:	b8 00 00 00 00       	mov    $0x0,%eax
  40205e:	e8 9d ed ff ff       	callq  400e00 <__printf_chk@plt>
  402063:	c7 05 af 34 20 00 00 	movl   $0x0,0x2034af(%rip)        # 60551c <vlevel>
  40206a:	00 00 00 
  40206d:	b8 00 00 00 00       	mov    $0x0,%eax
  402072:	e8 39 f9 ff ff       	callq  4019b0 <test>
  402077:	83 3d aa 34 20 00 00 	cmpl   $0x0,0x2034aa(%rip)        # 605528 <is_checker>
  40207e:	74 14                	je     402094 <launch+0x8d>
  402080:	bf 61 34 40 00       	mov    $0x403461,%edi
  402085:	e8 46 ec ff ff       	callq  400cd0 <puts@plt>
  40208a:	b8 00 00 00 00       	mov    $0x0,%eax
  40208f:	e8 d2 fa ff ff       	callq  401b66 <check_fail>
  402094:	bf 6c 34 40 00       	mov    $0x40346c,%edi
  402099:	e8 32 ec ff ff       	callq  400cd0 <puts@plt>
  40209e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4020a2:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4020a9:	00 00 
  4020ab:	74 05                	je     4020b2 <launch+0xab>
  4020ad:	e8 3e ec ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  4020b2:	c9                   	leaveq 
  4020b3:	c3                   	retq   

00000000004020b4 <stable_launch>:
  4020b4:	53                   	push   %rbx
  4020b5:	48 89 3d 4c 34 20 00 	mov    %rdi,0x20344c(%rip)        # 605508 <global_offset>
  4020bc:	41 b9 00 00 00 00    	mov    $0x0,%r9d
  4020c2:	41 b8 00 00 00 00    	mov    $0x0,%r8d
  4020c8:	b9 32 01 00 00       	mov    $0x132,%ecx
  4020cd:	ba 07 00 00 00       	mov    $0x7,%edx
  4020d2:	be 00 00 10 00       	mov    $0x100000,%esi
  4020d7:	bf 00 60 58 55       	mov    $0x55586000,%edi
  4020dc:	e8 1f ec ff ff       	callq  400d00 <mmap@plt>
  4020e1:	48 89 c3             	mov    %rax,%rbx
  4020e4:	48 3d 00 60 58 55    	cmp    $0x55586000,%rax
  4020ea:	74 37                	je     402123 <stable_launch+0x6f>
  4020ec:	be 00 00 10 00       	mov    $0x100000,%esi
  4020f1:	48 89 c7             	mov    %rax,%rdi
  4020f4:	e8 f7 ec ff ff       	callq  400df0 <munmap@plt>
  4020f9:	b9 00 60 58 55       	mov    $0x55586000,%ecx
  4020fe:	ba 20 36 40 00       	mov    $0x403620,%edx
  402103:	be 01 00 00 00       	mov    $0x1,%esi
  402108:	48 8b 3d d1 33 20 00 	mov    0x2033d1(%rip),%rdi        # 6054e0 <stderr@@GLIBC_2.2.5>
  40210f:	b8 00 00 00 00       	mov    $0x0,%eax
  402114:	e8 57 ed ff ff       	callq  400e70 <__fprintf_chk@plt>
  402119:	bf 01 00 00 00       	mov    $0x1,%edi
  40211e:	e8 2d ed ff ff       	callq  400e50 <exit@plt>
  402123:	48 8d 90 f8 ff 0f 00 	lea    0xffff8(%rax),%rdx
  40212a:	48 89 15 1f 40 20 00 	mov    %rdx,0x20401f(%rip)        # 606150 <stack_top>
  402131:	48 89 e0             	mov    %rsp,%rax
  402134:	48 89 d4             	mov    %rdx,%rsp
  402137:	48 89 c2             	mov    %rax,%rdx
  40213a:	48 89 15 bf 33 20 00 	mov    %rdx,0x2033bf(%rip)        # 605500 <global_save_stack>
  402141:	48 8b 3d c0 33 20 00 	mov    0x2033c0(%rip),%rdi        # 605508 <global_offset>
  402148:	e8 ba fe ff ff       	callq  402007 <launch>
  40214d:	48 8b 05 ac 33 20 00 	mov    0x2033ac(%rip),%rax        # 605500 <global_save_stack>
  402154:	48 89 c4             	mov    %rax,%rsp
  402157:	be 00 00 10 00       	mov    $0x100000,%esi
  40215c:	48 89 df             	mov    %rbx,%rdi
  40215f:	e8 8c ec ff ff       	callq  400df0 <munmap@plt>
  402164:	5b                   	pop    %rbx
  402165:	c3                   	retq   

0000000000402166 <rio_readinitb>:
  402166:	89 37                	mov    %esi,(%rdi)
  402168:	c7 47 04 00 00 00 00 	movl   $0x0,0x4(%rdi)
  40216f:	48 8d 47 10          	lea    0x10(%rdi),%rax
  402173:	48 89 47 08          	mov    %rax,0x8(%rdi)
  402177:	c3                   	retq   

0000000000402178 <sigalrm_handler>:
  402178:	48 83 ec 08          	sub    $0x8,%rsp
  40217c:	b9 00 00 00 00       	mov    $0x0,%ecx
  402181:	ba 60 36 40 00       	mov    $0x403660,%edx
  402186:	be 01 00 00 00       	mov    $0x1,%esi
  40218b:	48 8b 3d 4e 33 20 00 	mov    0x20334e(%rip),%rdi        # 6054e0 <stderr@@GLIBC_2.2.5>
  402192:	b8 00 00 00 00       	mov    $0x0,%eax
  402197:	e8 d4 ec ff ff       	callq  400e70 <__fprintf_chk@plt>
  40219c:	bf 01 00 00 00       	mov    $0x1,%edi
  4021a1:	e8 aa ec ff ff       	callq  400e50 <exit@plt>

00000000004021a6 <rio_writen>:
  4021a6:	41 55                	push   %r13
  4021a8:	41 54                	push   %r12
  4021aa:	55                   	push   %rbp
  4021ab:	53                   	push   %rbx
  4021ac:	48 83 ec 08          	sub    $0x8,%rsp
  4021b0:	41 89 fc             	mov    %edi,%r12d
  4021b3:	48 89 f5             	mov    %rsi,%rbp
  4021b6:	49 89 d5             	mov    %rdx,%r13
  4021b9:	48 89 d3             	mov    %rdx,%rbx
  4021bc:	eb 28                	jmp    4021e6 <rio_writen+0x40>
  4021be:	48 89 da             	mov    %rbx,%rdx
  4021c1:	48 89 ee             	mov    %rbp,%rsi
  4021c4:	44 89 e7             	mov    %r12d,%edi
  4021c7:	e8 14 eb ff ff       	callq  400ce0 <write@plt>
  4021cc:	48 85 c0             	test   %rax,%rax
  4021cf:	7f 0f                	jg     4021e0 <rio_writen+0x3a>
  4021d1:	e8 ba ea ff ff       	callq  400c90 <__errno_location@plt>
  4021d6:	83 38 04             	cmpl   $0x4,(%rax)
  4021d9:	75 15                	jne    4021f0 <rio_writen+0x4a>
  4021db:	b8 00 00 00 00       	mov    $0x0,%eax
  4021e0:	48 29 c3             	sub    %rax,%rbx
  4021e3:	48 01 c5             	add    %rax,%rbp
  4021e6:	48 85 db             	test   %rbx,%rbx
  4021e9:	75 d3                	jne    4021be <rio_writen+0x18>
  4021eb:	4c 89 e8             	mov    %r13,%rax
  4021ee:	eb 07                	jmp    4021f7 <rio_writen+0x51>
  4021f0:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  4021f7:	48 83 c4 08          	add    $0x8,%rsp
  4021fb:	5b                   	pop    %rbx
  4021fc:	5d                   	pop    %rbp
  4021fd:	41 5c                	pop    %r12
  4021ff:	41 5d                	pop    %r13
  402201:	c3                   	retq   

0000000000402202 <rio_read>:
  402202:	41 55                	push   %r13
  402204:	41 54                	push   %r12
  402206:	55                   	push   %rbp
  402207:	53                   	push   %rbx
  402208:	48 83 ec 08          	sub    $0x8,%rsp
  40220c:	48 89 fb             	mov    %rdi,%rbx
  40220f:	49 89 f5             	mov    %rsi,%r13
  402212:	49 89 d4             	mov    %rdx,%r12
  402215:	eb 2e                	jmp    402245 <rio_read+0x43>
  402217:	48 8d 6b 10          	lea    0x10(%rbx),%rbp
  40221b:	8b 3b                	mov    (%rbx),%edi
  40221d:	ba 00 20 00 00       	mov    $0x2000,%edx
  402222:	48 89 ee             	mov    %rbp,%rsi
  402225:	e8 16 eb ff ff       	callq  400d40 <read@plt>
  40222a:	89 43 04             	mov    %eax,0x4(%rbx)
  40222d:	85 c0                	test   %eax,%eax
  40222f:	79 0c                	jns    40223d <rio_read+0x3b>
  402231:	e8 5a ea ff ff       	callq  400c90 <__errno_location@plt>
  402236:	83 38 04             	cmpl   $0x4,(%rax)
  402239:	74 0a                	je     402245 <rio_read+0x43>
  40223b:	eb 37                	jmp    402274 <rio_read+0x72>
  40223d:	85 c0                	test   %eax,%eax
  40223f:	74 3c                	je     40227d <rio_read+0x7b>
  402241:	48 89 6b 08          	mov    %rbp,0x8(%rbx)
  402245:	8b 6b 04             	mov    0x4(%rbx),%ebp
  402248:	85 ed                	test   %ebp,%ebp
  40224a:	7e cb                	jle    402217 <rio_read+0x15>
  40224c:	89 e8                	mov    %ebp,%eax
  40224e:	49 39 c4             	cmp    %rax,%r12
  402251:	77 03                	ja     402256 <rio_read+0x54>
  402253:	44 89 e5             	mov    %r12d,%ebp
  402256:	4c 63 e5             	movslq %ebp,%r12
  402259:	48 8b 73 08          	mov    0x8(%rbx),%rsi
  40225d:	4c 89 e2             	mov    %r12,%rdx
  402260:	4c 89 ef             	mov    %r13,%rdi
  402263:	e8 38 eb ff ff       	callq  400da0 <memcpy@plt>
  402268:	4c 01 63 08          	add    %r12,0x8(%rbx)
  40226c:	29 6b 04             	sub    %ebp,0x4(%rbx)
  40226f:	4c 89 e0             	mov    %r12,%rax
  402272:	eb 0e                	jmp    402282 <rio_read+0x80>
  402274:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  40227b:	eb 05                	jmp    402282 <rio_read+0x80>
  40227d:	b8 00 00 00 00       	mov    $0x0,%eax
  402282:	48 83 c4 08          	add    $0x8,%rsp
  402286:	5b                   	pop    %rbx
  402287:	5d                   	pop    %rbp
  402288:	41 5c                	pop    %r12
  40228a:	41 5d                	pop    %r13
  40228c:	c3                   	retq   

000000000040228d <rio_readlineb>:
  40228d:	41 55                	push   %r13
  40228f:	41 54                	push   %r12
  402291:	55                   	push   %rbp
  402292:	53                   	push   %rbx
  402293:	48 83 ec 18          	sub    $0x18,%rsp
  402297:	49 89 fd             	mov    %rdi,%r13
  40229a:	48 89 f5             	mov    %rsi,%rbp
  40229d:	49 89 d4             	mov    %rdx,%r12
  4022a0:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4022a7:	00 00 
  4022a9:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  4022ae:	31 c0                	xor    %eax,%eax
  4022b0:	bb 01 00 00 00       	mov    $0x1,%ebx
  4022b5:	eb 3f                	jmp    4022f6 <rio_readlineb+0x69>
  4022b7:	ba 01 00 00 00       	mov    $0x1,%edx
  4022bc:	48 8d 74 24 07       	lea    0x7(%rsp),%rsi
  4022c1:	4c 89 ef             	mov    %r13,%rdi
  4022c4:	e8 39 ff ff ff       	callq  402202 <rio_read>
  4022c9:	83 f8 01             	cmp    $0x1,%eax
  4022cc:	75 15                	jne    4022e3 <rio_readlineb+0x56>
  4022ce:	48 8d 45 01          	lea    0x1(%rbp),%rax
  4022d2:	0f b6 54 24 07       	movzbl 0x7(%rsp),%edx
  4022d7:	88 55 00             	mov    %dl,0x0(%rbp)
  4022da:	80 7c 24 07 0a       	cmpb   $0xa,0x7(%rsp)
  4022df:	75 0e                	jne    4022ef <rio_readlineb+0x62>
  4022e1:	eb 1a                	jmp    4022fd <rio_readlineb+0x70>
  4022e3:	85 c0                	test   %eax,%eax
  4022e5:	75 22                	jne    402309 <rio_readlineb+0x7c>
  4022e7:	48 83 fb 01          	cmp    $0x1,%rbx
  4022eb:	75 13                	jne    402300 <rio_readlineb+0x73>
  4022ed:	eb 23                	jmp    402312 <rio_readlineb+0x85>
  4022ef:	48 83 c3 01          	add    $0x1,%rbx
  4022f3:	48 89 c5             	mov    %rax,%rbp
  4022f6:	4c 39 e3             	cmp    %r12,%rbx
  4022f9:	72 bc                	jb     4022b7 <rio_readlineb+0x2a>
  4022fb:	eb 03                	jmp    402300 <rio_readlineb+0x73>
  4022fd:	48 89 c5             	mov    %rax,%rbp
  402300:	c6 45 00 00          	movb   $0x0,0x0(%rbp)
  402304:	48 89 d8             	mov    %rbx,%rax
  402307:	eb 0e                	jmp    402317 <rio_readlineb+0x8a>
  402309:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  402310:	eb 05                	jmp    402317 <rio_readlineb+0x8a>
  402312:	b8 00 00 00 00       	mov    $0x0,%eax
  402317:	48 8b 4c 24 08       	mov    0x8(%rsp),%rcx
  40231c:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  402323:	00 00 
  402325:	74 05                	je     40232c <rio_readlineb+0x9f>
  402327:	e8 c4 e9 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  40232c:	48 83 c4 18          	add    $0x18,%rsp
  402330:	5b                   	pop    %rbx
  402331:	5d                   	pop    %rbp
  402332:	41 5c                	pop    %r12
  402334:	41 5d                	pop    %r13
  402336:	c3                   	retq   

0000000000402337 <urlencode>:
  402337:	41 54                	push   %r12
  402339:	55                   	push   %rbp
  40233a:	53                   	push   %rbx
  40233b:	48 83 ec 10          	sub    $0x10,%rsp
  40233f:	48 89 fb             	mov    %rdi,%rbx
  402342:	48 89 f5             	mov    %rsi,%rbp
  402345:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  40234c:	00 00 
  40234e:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  402353:	31 c0                	xor    %eax,%eax
  402355:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  40235c:	f2 ae                	repnz scas %es:(%rdi),%al
  40235e:	48 f7 d1             	not    %rcx
  402361:	8d 41 ff             	lea    -0x1(%rcx),%eax
  402364:	e9 aa 00 00 00       	jmpq   402413 <urlencode+0xdc>
  402369:	44 0f b6 03          	movzbl (%rbx),%r8d
  40236d:	41 80 f8 2a          	cmp    $0x2a,%r8b
  402371:	0f 94 c2             	sete   %dl
  402374:	41 80 f8 2d          	cmp    $0x2d,%r8b
  402378:	0f 94 c0             	sete   %al
  40237b:	08 c2                	or     %al,%dl
  40237d:	75 24                	jne    4023a3 <urlencode+0x6c>
  40237f:	41 80 f8 2e          	cmp    $0x2e,%r8b
  402383:	74 1e                	je     4023a3 <urlencode+0x6c>
  402385:	41 80 f8 5f          	cmp    $0x5f,%r8b
  402389:	74 18                	je     4023a3 <urlencode+0x6c>
  40238b:	41 8d 40 d0          	lea    -0x30(%r8),%eax
  40238f:	3c 09                	cmp    $0x9,%al
  402391:	76 10                	jbe    4023a3 <urlencode+0x6c>
  402393:	41 8d 40 bf          	lea    -0x41(%r8),%eax
  402397:	3c 19                	cmp    $0x19,%al
  402399:	76 08                	jbe    4023a3 <urlencode+0x6c>
  40239b:	41 8d 40 9f          	lea    -0x61(%r8),%eax
  40239f:	3c 19                	cmp    $0x19,%al
  4023a1:	77 0a                	ja     4023ad <urlencode+0x76>
  4023a3:	44 88 45 00          	mov    %r8b,0x0(%rbp)
  4023a7:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  4023ab:	eb 5f                	jmp    40240c <urlencode+0xd5>
  4023ad:	41 80 f8 20          	cmp    $0x20,%r8b
  4023b1:	75 0a                	jne    4023bd <urlencode+0x86>
  4023b3:	c6 45 00 2b          	movb   $0x2b,0x0(%rbp)
  4023b7:	48 8d 6d 01          	lea    0x1(%rbp),%rbp
  4023bb:	eb 4f                	jmp    40240c <urlencode+0xd5>
  4023bd:	41 8d 40 e0          	lea    -0x20(%r8),%eax
  4023c1:	3c 5f                	cmp    $0x5f,%al
  4023c3:	0f 96 c2             	setbe  %dl
  4023c6:	41 80 f8 09          	cmp    $0x9,%r8b
  4023ca:	0f 94 c0             	sete   %al
  4023cd:	08 c2                	or     %al,%dl
  4023cf:	74 50                	je     402421 <urlencode+0xea>
  4023d1:	45 0f b6 c0          	movzbl %r8b,%r8d
  4023d5:	b9 f8 36 40 00       	mov    $0x4036f8,%ecx
  4023da:	ba 08 00 00 00       	mov    $0x8,%edx
  4023df:	be 01 00 00 00       	mov    $0x1,%esi
  4023e4:	48 89 e7             	mov    %rsp,%rdi
  4023e7:	b8 00 00 00 00       	mov    $0x0,%eax
  4023ec:	e8 8f ea ff ff       	callq  400e80 <__sprintf_chk@plt>
  4023f1:	0f b6 04 24          	movzbl (%rsp),%eax
  4023f5:	88 45 00             	mov    %al,0x0(%rbp)
  4023f8:	0f b6 44 24 01       	movzbl 0x1(%rsp),%eax
  4023fd:	88 45 01             	mov    %al,0x1(%rbp)
  402400:	0f b6 44 24 02       	movzbl 0x2(%rsp),%eax
  402405:	88 45 02             	mov    %al,0x2(%rbp)
  402408:	48 8d 6d 03          	lea    0x3(%rbp),%rbp
  40240c:	48 83 c3 01          	add    $0x1,%rbx
  402410:	44 89 e0             	mov    %r12d,%eax
  402413:	44 8d 60 ff          	lea    -0x1(%rax),%r12d
  402417:	85 c0                	test   %eax,%eax
  402419:	0f 85 4a ff ff ff    	jne    402369 <urlencode+0x32>
  40241f:	eb 05                	jmp    402426 <urlencode+0xef>
  402421:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402426:	48 8b 74 24 08       	mov    0x8(%rsp),%rsi
  40242b:	64 48 33 34 25 28 00 	xor    %fs:0x28,%rsi
  402432:	00 00 
  402434:	74 05                	je     40243b <urlencode+0x104>
  402436:	e8 b5 e8 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  40243b:	48 83 c4 10          	add    $0x10,%rsp
  40243f:	5b                   	pop    %rbx
  402440:	5d                   	pop    %rbp
  402441:	41 5c                	pop    %r12
  402443:	c3                   	retq   

0000000000402444 <submitr>:
  402444:	41 57                	push   %r15
  402446:	41 56                	push   %r14
  402448:	41 55                	push   %r13
  40244a:	41 54                	push   %r12
  40244c:	55                   	push   %rbp
  40244d:	53                   	push   %rbx
  40244e:	48 81 ec 58 a0 00 00 	sub    $0xa058,%rsp
  402455:	49 89 fc             	mov    %rdi,%r12
  402458:	89 74 24 04          	mov    %esi,0x4(%rsp)
  40245c:	49 89 d7             	mov    %rdx,%r15
  40245f:	49 89 ce             	mov    %rcx,%r14
  402462:	4c 89 44 24 08       	mov    %r8,0x8(%rsp)
  402467:	4d 89 cd             	mov    %r9,%r13
  40246a:	48 8b 9c 24 90 a0 00 	mov    0xa090(%rsp),%rbx
  402471:	00 
  402472:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  402479:	00 00 
  40247b:	48 89 84 24 48 a0 00 	mov    %rax,0xa048(%rsp)
  402482:	00 
  402483:	31 c0                	xor    %eax,%eax
  402485:	c7 44 24 1c 00 00 00 	movl   $0x0,0x1c(%rsp)
  40248c:	00 
  40248d:	ba 00 00 00 00       	mov    $0x0,%edx
  402492:	be 01 00 00 00       	mov    $0x1,%esi
  402497:	bf 02 00 00 00       	mov    $0x2,%edi
  40249c:	e8 ef e9 ff ff       	callq  400e90 <socket@plt>
  4024a1:	85 c0                	test   %eax,%eax
  4024a3:	79 4e                	jns    4024f3 <submitr+0xaf>
  4024a5:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  4024ac:	3a 20 43 
  4024af:	48 89 03             	mov    %rax,(%rbx)
  4024b2:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4024b9:	20 75 6e 
  4024bc:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4024c0:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4024c7:	74 6f 20 
  4024ca:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4024ce:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  4024d5:	65 20 73 
  4024d8:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4024dc:	c7 43 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbx)
  4024e3:	66 c7 43 24 74 00    	movw   $0x74,0x24(%rbx)
  4024e9:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4024ee:	e9 97 06 00 00       	jmpq   402b8a <submitr+0x746>
  4024f3:	89 c5                	mov    %eax,%ebp
  4024f5:	4c 89 e7             	mov    %r12,%rdi
  4024f8:	e8 73 e8 ff ff       	callq  400d70 <gethostbyname@plt>
  4024fd:	48 85 c0             	test   %rax,%rax
  402500:	75 67                	jne    402569 <submitr+0x125>
  402502:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  402509:	3a 20 44 
  40250c:	48 89 03             	mov    %rax,(%rbx)
  40250f:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  402516:	20 75 6e 
  402519:	48 89 43 08          	mov    %rax,0x8(%rbx)
  40251d:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402524:	74 6f 20 
  402527:	48 89 43 10          	mov    %rax,0x10(%rbx)
  40252b:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  402532:	76 65 20 
  402535:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402539:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  402540:	72 20 61 
  402543:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402547:	c7 43 28 64 64 72 65 	movl   $0x65726464,0x28(%rbx)
  40254e:	66 c7 43 2c 73 73    	movw   $0x7373,0x2c(%rbx)
  402554:	c6 43 2e 00          	movb   $0x0,0x2e(%rbx)
  402558:	89 ef                	mov    %ebp,%edi
  40255a:	e8 d1 e7 ff ff       	callq  400d30 <close@plt>
  40255f:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402564:	e9 21 06 00 00       	jmpq   402b8a <submitr+0x746>
  402569:	48 c7 44 24 20 00 00 	movq   $0x0,0x20(%rsp)
  402570:	00 00 
  402572:	48 c7 44 24 28 00 00 	movq   $0x0,0x28(%rsp)
  402579:	00 00 
  40257b:	66 c7 44 24 20 02 00 	movw   $0x2,0x20(%rsp)
  402582:	48 63 50 14          	movslq 0x14(%rax),%rdx
  402586:	48 8b 40 18          	mov    0x18(%rax),%rax
  40258a:	48 8b 30             	mov    (%rax),%rsi
  40258d:	48 8d 7c 24 24       	lea    0x24(%rsp),%rdi
  402592:	b9 0c 00 00 00       	mov    $0xc,%ecx
  402597:	e8 e4 e7 ff ff       	callq  400d80 <__memmove_chk@plt>
  40259c:	0f b7 44 24 04       	movzwl 0x4(%rsp),%eax
  4025a1:	66 c1 c8 08          	ror    $0x8,%ax
  4025a5:	66 89 44 24 22       	mov    %ax,0x22(%rsp)
  4025aa:	ba 10 00 00 00       	mov    $0x10,%edx
  4025af:	48 8d 74 24 20       	lea    0x20(%rsp),%rsi
  4025b4:	89 ef                	mov    %ebp,%edi
  4025b6:	e8 a5 e8 ff ff       	callq  400e60 <connect@plt>
  4025bb:	85 c0                	test   %eax,%eax
  4025bd:	79 59                	jns    402618 <submitr+0x1d4>
  4025bf:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  4025c6:	3a 20 55 
  4025c9:	48 89 03             	mov    %rax,(%rbx)
  4025cc:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  4025d3:	20 74 6f 
  4025d6:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4025da:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  4025e1:	65 63 74 
  4025e4:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4025e8:	48 b8 20 74 6f 20 74 	movabs $0x20656874206f7420,%rax
  4025ef:	68 65 20 
  4025f2:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4025f6:	c7 43 20 73 65 72 76 	movl   $0x76726573,0x20(%rbx)
  4025fd:	66 c7 43 24 65 72    	movw   $0x7265,0x24(%rbx)
  402603:	c6 43 26 00          	movb   $0x0,0x26(%rbx)
  402607:	89 ef                	mov    %ebp,%edi
  402609:	e8 22 e7 ff ff       	callq  400d30 <close@plt>
  40260e:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402613:	e9 72 05 00 00       	jmpq   402b8a <submitr+0x746>
  402618:	48 c7 c6 ff ff ff ff 	mov    $0xffffffffffffffff,%rsi
  40261f:	b8 00 00 00 00       	mov    $0x0,%eax
  402624:	48 89 f1             	mov    %rsi,%rcx
  402627:	4c 89 ef             	mov    %r13,%rdi
  40262a:	f2 ae                	repnz scas %es:(%rdi),%al
  40262c:	48 f7 d1             	not    %rcx
  40262f:	48 89 ca             	mov    %rcx,%rdx
  402632:	48 89 f1             	mov    %rsi,%rcx
  402635:	4c 89 ff             	mov    %r15,%rdi
  402638:	f2 ae                	repnz scas %es:(%rdi),%al
  40263a:	48 f7 d1             	not    %rcx
  40263d:	49 89 c8             	mov    %rcx,%r8
  402640:	48 89 f1             	mov    %rsi,%rcx
  402643:	4c 89 f7             	mov    %r14,%rdi
  402646:	f2 ae                	repnz scas %es:(%rdi),%al
  402648:	48 f7 d1             	not    %rcx
  40264b:	4d 8d 44 08 fe       	lea    -0x2(%r8,%rcx,1),%r8
  402650:	48 89 f1             	mov    %rsi,%rcx
  402653:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
  402658:	f2 ae                	repnz scas %es:(%rdi),%al
  40265a:	48 89 c8             	mov    %rcx,%rax
  40265d:	48 f7 d0             	not    %rax
  402660:	49 8d 4c 00 ff       	lea    -0x1(%r8,%rax,1),%rcx
  402665:	48 8d 44 52 fd       	lea    -0x3(%rdx,%rdx,2),%rax
  40266a:	48 8d 84 01 80 00 00 	lea    0x80(%rcx,%rax,1),%rax
  402671:	00 
  402672:	48 3d 00 20 00 00    	cmp    $0x2000,%rax
  402678:	76 72                	jbe    4026ec <submitr+0x2a8>
  40267a:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  402681:	3a 20 52 
  402684:	48 89 03             	mov    %rax,(%rbx)
  402687:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  40268e:	20 73 74 
  402691:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402695:	48 b8 72 69 6e 67 20 	movabs $0x6f6f7420676e6972,%rax
  40269c:	74 6f 6f 
  40269f:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4026a3:	48 b8 20 6c 61 72 67 	movabs $0x202e656772616c20,%rax
  4026aa:	65 2e 20 
  4026ad:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4026b1:	48 b8 49 6e 63 72 65 	movabs $0x6573616572636e49,%rax
  4026b8:	61 73 65 
  4026bb:	48 89 43 20          	mov    %rax,0x20(%rbx)
  4026bf:	48 b8 20 53 55 42 4d 	movabs $0x5254494d42555320,%rax
  4026c6:	49 54 52 
  4026c9:	48 89 43 28          	mov    %rax,0x28(%rbx)
  4026cd:	48 b8 5f 4d 41 58 42 	movabs $0x46554258414d5f,%rax
  4026d4:	55 46 00 
  4026d7:	48 89 43 30          	mov    %rax,0x30(%rbx)
  4026db:	89 ef                	mov    %ebp,%edi
  4026dd:	e8 4e e6 ff ff       	callq  400d30 <close@plt>
  4026e2:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4026e7:	e9 9e 04 00 00       	jmpq   402b8a <submitr+0x746>
  4026ec:	48 8d b4 24 40 40 00 	lea    0x4040(%rsp),%rsi
  4026f3:	00 
  4026f4:	b9 00 04 00 00       	mov    $0x400,%ecx
  4026f9:	b8 00 00 00 00       	mov    $0x0,%eax
  4026fe:	48 89 f7             	mov    %rsi,%rdi
  402701:	f3 48 ab             	rep stos %rax,%es:(%rdi)
  402704:	4c 89 ef             	mov    %r13,%rdi
  402707:	e8 2b fc ff ff       	callq  402337 <urlencode>
  40270c:	85 c0                	test   %eax,%eax
  40270e:	0f 89 8a 00 00 00    	jns    40279e <submitr+0x35a>
  402714:	48 b8 45 72 72 6f 72 	movabs $0x52203a726f727245,%rax
  40271b:	3a 20 52 
  40271e:	48 89 03             	mov    %rax,(%rbx)
  402721:	48 b8 65 73 75 6c 74 	movabs $0x747320746c757365,%rax
  402728:	20 73 74 
  40272b:	48 89 43 08          	mov    %rax,0x8(%rbx)
  40272f:	48 b8 72 69 6e 67 20 	movabs $0x6e6f6320676e6972,%rax
  402736:	63 6f 6e 
  402739:	48 89 43 10          	mov    %rax,0x10(%rbx)
  40273d:	48 b8 74 61 69 6e 73 	movabs $0x6e6120736e696174,%rax
  402744:	20 61 6e 
  402747:	48 89 43 18          	mov    %rax,0x18(%rbx)
  40274b:	48 b8 20 69 6c 6c 65 	movabs $0x6c6167656c6c6920,%rax
  402752:	67 61 6c 
  402755:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402759:	48 b8 20 6f 72 20 75 	movabs $0x72706e7520726f20,%rax
  402760:	6e 70 72 
  402763:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402767:	48 b8 69 6e 74 61 62 	movabs $0x20656c6261746e69,%rax
  40276e:	6c 65 20 
  402771:	48 89 43 30          	mov    %rax,0x30(%rbx)
  402775:	48 b8 63 68 61 72 61 	movabs $0x6574636172616863,%rax
  40277c:	63 74 65 
  40277f:	48 89 43 38          	mov    %rax,0x38(%rbx)
  402783:	66 c7 43 40 72 2e    	movw   $0x2e72,0x40(%rbx)
  402789:	c6 43 42 00          	movb   $0x0,0x42(%rbx)
  40278d:	89 ef                	mov    %ebp,%edi
  40278f:	e8 9c e5 ff ff       	callq  400d30 <close@plt>
  402794:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402799:	e9 ec 03 00 00       	jmpq   402b8a <submitr+0x746>
  40279e:	4c 8d ac 24 40 20 00 	lea    0x2040(%rsp),%r13
  4027a5:	00 
  4027a6:	41 54                	push   %r12
  4027a8:	48 8d 84 24 48 40 00 	lea    0x4048(%rsp),%rax
  4027af:	00 
  4027b0:	50                   	push   %rax
  4027b1:	4d 89 f9             	mov    %r15,%r9
  4027b4:	4d 89 f0             	mov    %r14,%r8
  4027b7:	b9 88 36 40 00       	mov    $0x403688,%ecx
  4027bc:	ba 00 20 00 00       	mov    $0x2000,%edx
  4027c1:	be 01 00 00 00       	mov    $0x1,%esi
  4027c6:	4c 89 ef             	mov    %r13,%rdi
  4027c9:	b8 00 00 00 00       	mov    $0x0,%eax
  4027ce:	e8 ad e6 ff ff       	callq  400e80 <__sprintf_chk@plt>
  4027d3:	b8 00 00 00 00       	mov    $0x0,%eax
  4027d8:	48 c7 c1 ff ff ff ff 	mov    $0xffffffffffffffff,%rcx
  4027df:	4c 89 ef             	mov    %r13,%rdi
  4027e2:	f2 ae                	repnz scas %es:(%rdi),%al
  4027e4:	48 f7 d1             	not    %rcx
  4027e7:	48 8d 51 ff          	lea    -0x1(%rcx),%rdx
  4027eb:	4c 89 ee             	mov    %r13,%rsi
  4027ee:	89 ef                	mov    %ebp,%edi
  4027f0:	e8 b1 f9 ff ff       	callq  4021a6 <rio_writen>
  4027f5:	48 83 c4 10          	add    $0x10,%rsp
  4027f9:	48 85 c0             	test   %rax,%rax
  4027fc:	79 6e                	jns    40286c <submitr+0x428>
  4027fe:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402805:	3a 20 43 
  402808:	48 89 03             	mov    %rax,(%rbx)
  40280b:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402812:	20 75 6e 
  402815:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402819:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402820:	74 6f 20 
  402823:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402827:	48 b8 77 72 69 74 65 	movabs $0x6f74206574697277,%rax
  40282e:	20 74 6f 
  402831:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402835:	48 b8 20 74 68 65 20 	movabs $0x7365722065687420,%rax
  40283c:	72 65 73 
  40283f:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402843:	48 b8 75 6c 74 20 73 	movabs $0x7672657320746c75,%rax
  40284a:	65 72 76 
  40284d:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402851:	66 c7 43 30 65 72    	movw   $0x7265,0x30(%rbx)
  402857:	c6 43 32 00          	movb   $0x0,0x32(%rbx)
  40285b:	89 ef                	mov    %ebp,%edi
  40285d:	e8 ce e4 ff ff       	callq  400d30 <close@plt>
  402862:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402867:	e9 1e 03 00 00       	jmpq   402b8a <submitr+0x746>
  40286c:	89 ee                	mov    %ebp,%esi
  40286e:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  402873:	e8 ee f8 ff ff       	callq  402166 <rio_readinitb>
  402878:	ba 00 20 00 00       	mov    $0x2000,%edx
  40287d:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  402884:	00 
  402885:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  40288a:	e8 fe f9 ff ff       	callq  40228d <rio_readlineb>
  40288f:	48 85 c0             	test   %rax,%rax
  402892:	7f 7d                	jg     402911 <submitr+0x4cd>
  402894:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  40289b:	3a 20 43 
  40289e:	48 89 03             	mov    %rax,(%rbx)
  4028a1:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  4028a8:	20 75 6e 
  4028ab:	48 89 43 08          	mov    %rax,0x8(%rbx)
  4028af:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  4028b6:	74 6f 20 
  4028b9:	48 89 43 10          	mov    %rax,0x10(%rbx)
  4028bd:	48 b8 72 65 61 64 20 	movabs $0x7269662064616572,%rax
  4028c4:	66 69 72 
  4028c7:	48 89 43 18          	mov    %rax,0x18(%rbx)
  4028cb:	48 b8 73 74 20 68 65 	movabs $0x6564616568207473,%rax
  4028d2:	61 64 65 
  4028d5:	48 89 43 20          	mov    %rax,0x20(%rbx)
  4028d9:	48 b8 72 20 66 72 6f 	movabs $0x72206d6f72662072,%rax
  4028e0:	6d 20 72 
  4028e3:	48 89 43 28          	mov    %rax,0x28(%rbx)
  4028e7:	48 b8 65 73 75 6c 74 	movabs $0x657320746c757365,%rax
  4028ee:	20 73 65 
  4028f1:	48 89 43 30          	mov    %rax,0x30(%rbx)
  4028f5:	c7 43 38 72 76 65 72 	movl   $0x72657672,0x38(%rbx)
  4028fc:	c6 43 3c 00          	movb   $0x0,0x3c(%rbx)
  402900:	89 ef                	mov    %ebp,%edi
  402902:	e8 29 e4 ff ff       	callq  400d30 <close@plt>
  402907:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  40290c:	e9 79 02 00 00       	jmpq   402b8a <submitr+0x746>
  402911:	4c 8d 84 24 40 80 00 	lea    0x8040(%rsp),%r8
  402918:	00 
  402919:	48 8d 4c 24 1c       	lea    0x1c(%rsp),%rcx
  40291e:	48 8d 94 24 40 60 00 	lea    0x6040(%rsp),%rdx
  402925:	00 
  402926:	be ff 36 40 00       	mov    $0x4036ff,%esi
  40292b:	48 8d bc 24 40 20 00 	lea    0x2040(%rsp),%rdi
  402932:	00 
  402933:	b8 00 00 00 00       	mov    $0x0,%eax
  402938:	e8 a3 e4 ff ff       	callq  400de0 <__isoc99_sscanf@plt>
  40293d:	e9 95 00 00 00       	jmpq   4029d7 <submitr+0x593>
  402942:	ba 00 20 00 00       	mov    $0x2000,%edx
  402947:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  40294e:	00 
  40294f:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  402954:	e8 34 f9 ff ff       	callq  40228d <rio_readlineb>
  402959:	48 85 c0             	test   %rax,%rax
  40295c:	7f 79                	jg     4029d7 <submitr+0x593>
  40295e:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402965:	3a 20 43 
  402968:	48 89 03             	mov    %rax,(%rbx)
  40296b:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402972:	20 75 6e 
  402975:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402979:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402980:	74 6f 20 
  402983:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402987:	48 b8 72 65 61 64 20 	movabs $0x6165682064616572,%rax
  40298e:	68 65 61 
  402991:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402995:	48 b8 64 65 72 73 20 	movabs $0x6f72662073726564,%rax
  40299c:	66 72 6f 
  40299f:	48 89 43 20          	mov    %rax,0x20(%rbx)
  4029a3:	48 b8 6d 20 74 68 65 	movabs $0x657220656874206d,%rax
  4029aa:	20 72 65 
  4029ad:	48 89 43 28          	mov    %rax,0x28(%rbx)
  4029b1:	48 b8 73 75 6c 74 20 	movabs $0x72657320746c7573,%rax
  4029b8:	73 65 72 
  4029bb:	48 89 43 30          	mov    %rax,0x30(%rbx)
  4029bf:	c7 43 38 76 65 72 00 	movl   $0x726576,0x38(%rbx)
  4029c6:	89 ef                	mov    %ebp,%edi
  4029c8:	e8 63 e3 ff ff       	callq  400d30 <close@plt>
  4029cd:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  4029d2:	e9 b3 01 00 00       	jmpq   402b8a <submitr+0x746>
  4029d7:	0f b6 94 24 40 20 00 	movzbl 0x2040(%rsp),%edx
  4029de:	00 
  4029df:	b8 0d 00 00 00       	mov    $0xd,%eax
  4029e4:	29 d0                	sub    %edx,%eax
  4029e6:	75 1b                	jne    402a03 <submitr+0x5bf>
  4029e8:	0f b6 94 24 41 20 00 	movzbl 0x2041(%rsp),%edx
  4029ef:	00 
  4029f0:	b8 0a 00 00 00       	mov    $0xa,%eax
  4029f5:	29 d0                	sub    %edx,%eax
  4029f7:	75 0a                	jne    402a03 <submitr+0x5bf>
  4029f9:	0f b6 84 24 42 20 00 	movzbl 0x2042(%rsp),%eax
  402a00:	00 
  402a01:	f7 d8                	neg    %eax
  402a03:	85 c0                	test   %eax,%eax
  402a05:	0f 85 37 ff ff ff    	jne    402942 <submitr+0x4fe>
  402a0b:	ba 00 20 00 00       	mov    $0x2000,%edx
  402a10:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  402a17:	00 
  402a18:	48 8d 7c 24 30       	lea    0x30(%rsp),%rdi
  402a1d:	e8 6b f8 ff ff       	callq  40228d <rio_readlineb>
  402a22:	48 85 c0             	test   %rax,%rax
  402a25:	0f 8f 83 00 00 00    	jg     402aae <submitr+0x66a>
  402a2b:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402a32:	3a 20 43 
  402a35:	48 89 03             	mov    %rax,(%rbx)
  402a38:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402a3f:	20 75 6e 
  402a42:	48 89 43 08          	mov    %rax,0x8(%rbx)
  402a46:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402a4d:	74 6f 20 
  402a50:	48 89 43 10          	mov    %rax,0x10(%rbx)
  402a54:	48 b8 72 65 61 64 20 	movabs $0x6174732064616572,%rax
  402a5b:	73 74 61 
  402a5e:	48 89 43 18          	mov    %rax,0x18(%rbx)
  402a62:	48 b8 74 75 73 20 6d 	movabs $0x7373656d20737574,%rax
  402a69:	65 73 73 
  402a6c:	48 89 43 20          	mov    %rax,0x20(%rbx)
  402a70:	48 b8 61 67 65 20 66 	movabs $0x6d6f726620656761,%rax
  402a77:	72 6f 6d 
  402a7a:	48 89 43 28          	mov    %rax,0x28(%rbx)
  402a7e:	48 b8 20 72 65 73 75 	movabs $0x20746c7573657220,%rax
  402a85:	6c 74 20 
  402a88:	48 89 43 30          	mov    %rax,0x30(%rbx)
  402a8c:	c7 43 38 73 65 72 76 	movl   $0x76726573,0x38(%rbx)
  402a93:	66 c7 43 3c 65 72    	movw   $0x7265,0x3c(%rbx)
  402a99:	c6 43 3e 00          	movb   $0x0,0x3e(%rbx)
  402a9d:	89 ef                	mov    %ebp,%edi
  402a9f:	e8 8c e2 ff ff       	callq  400d30 <close@plt>
  402aa4:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402aa9:	e9 dc 00 00 00       	jmpq   402b8a <submitr+0x746>
  402aae:	44 8b 44 24 1c       	mov    0x1c(%rsp),%r8d
  402ab3:	41 81 f8 c8 00 00 00 	cmp    $0xc8,%r8d
  402aba:	74 37                	je     402af3 <submitr+0x6af>
  402abc:	4c 8d 8c 24 40 80 00 	lea    0x8040(%rsp),%r9
  402ac3:	00 
  402ac4:	b9 c8 36 40 00       	mov    $0x4036c8,%ecx
  402ac9:	48 c7 c2 ff ff ff ff 	mov    $0xffffffffffffffff,%rdx
  402ad0:	be 01 00 00 00       	mov    $0x1,%esi
  402ad5:	48 89 df             	mov    %rbx,%rdi
  402ad8:	b8 00 00 00 00       	mov    $0x0,%eax
  402add:	e8 9e e3 ff ff       	callq  400e80 <__sprintf_chk@plt>
  402ae2:	89 ef                	mov    %ebp,%edi
  402ae4:	e8 47 e2 ff ff       	callq  400d30 <close@plt>
  402ae9:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402aee:	e9 97 00 00 00       	jmpq   402b8a <submitr+0x746>
  402af3:	48 8d b4 24 40 20 00 	lea    0x2040(%rsp),%rsi
  402afa:	00 
  402afb:	48 89 df             	mov    %rbx,%rdi
  402afe:	e8 bd e1 ff ff       	callq  400cc0 <strcpy@plt>
  402b03:	89 ef                	mov    %ebp,%edi
  402b05:	e8 26 e2 ff ff       	callq  400d30 <close@plt>
  402b0a:	0f b6 03             	movzbl (%rbx),%eax
  402b0d:	ba 4f 00 00 00       	mov    $0x4f,%edx
  402b12:	29 c2                	sub    %eax,%edx
  402b14:	75 22                	jne    402b38 <submitr+0x6f4>
  402b16:	0f b6 4b 01          	movzbl 0x1(%rbx),%ecx
  402b1a:	b8 4b 00 00 00       	mov    $0x4b,%eax
  402b1f:	29 c8                	sub    %ecx,%eax
  402b21:	75 17                	jne    402b3a <submitr+0x6f6>
  402b23:	0f b6 4b 02          	movzbl 0x2(%rbx),%ecx
  402b27:	b8 0a 00 00 00       	mov    $0xa,%eax
  402b2c:	29 c8                	sub    %ecx,%eax
  402b2e:	75 0a                	jne    402b3a <submitr+0x6f6>
  402b30:	0f b6 43 03          	movzbl 0x3(%rbx),%eax
  402b34:	f7 d8                	neg    %eax
  402b36:	eb 02                	jmp    402b3a <submitr+0x6f6>
  402b38:	89 d0                	mov    %edx,%eax
  402b3a:	85 c0                	test   %eax,%eax
  402b3c:	74 40                	je     402b7e <submitr+0x73a>
  402b3e:	bf 10 37 40 00       	mov    $0x403710,%edi
  402b43:	b9 05 00 00 00       	mov    $0x5,%ecx
  402b48:	48 89 de             	mov    %rbx,%rsi
  402b4b:	f3 a6                	repz cmpsb %es:(%rdi),%ds:(%rsi)
  402b4d:	0f 97 c0             	seta   %al
  402b50:	0f 92 c1             	setb   %cl
  402b53:	29 c8                	sub    %ecx,%eax
  402b55:	0f be c0             	movsbl %al,%eax
  402b58:	85 c0                	test   %eax,%eax
  402b5a:	74 2e                	je     402b8a <submitr+0x746>
  402b5c:	85 d2                	test   %edx,%edx
  402b5e:	75 13                	jne    402b73 <submitr+0x72f>
  402b60:	0f b6 43 01          	movzbl 0x1(%rbx),%eax
  402b64:	ba 4b 00 00 00       	mov    $0x4b,%edx
  402b69:	29 c2                	sub    %eax,%edx
  402b6b:	75 06                	jne    402b73 <submitr+0x72f>
  402b6d:	0f b6 53 02          	movzbl 0x2(%rbx),%edx
  402b71:	f7 da                	neg    %edx
  402b73:	85 d2                	test   %edx,%edx
  402b75:	75 0e                	jne    402b85 <submitr+0x741>
  402b77:	b8 00 00 00 00       	mov    $0x0,%eax
  402b7c:	eb 0c                	jmp    402b8a <submitr+0x746>
  402b7e:	b8 00 00 00 00       	mov    $0x0,%eax
  402b83:	eb 05                	jmp    402b8a <submitr+0x746>
  402b85:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402b8a:	48 8b 9c 24 48 a0 00 	mov    0xa048(%rsp),%rbx
  402b91:	00 
  402b92:	64 48 33 1c 25 28 00 	xor    %fs:0x28,%rbx
  402b99:	00 00 
  402b9b:	74 05                	je     402ba2 <submitr+0x75e>
  402b9d:	e8 4e e1 ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  402ba2:	48 81 c4 58 a0 00 00 	add    $0xa058,%rsp
  402ba9:	5b                   	pop    %rbx
  402baa:	5d                   	pop    %rbp
  402bab:	41 5c                	pop    %r12
  402bad:	41 5d                	pop    %r13
  402baf:	41 5e                	pop    %r14
  402bb1:	41 5f                	pop    %r15
  402bb3:	c3                   	retq   

0000000000402bb4 <init_timeout>:
  402bb4:	85 ff                	test   %edi,%edi
  402bb6:	74 23                	je     402bdb <init_timeout+0x27>
  402bb8:	53                   	push   %rbx
  402bb9:	89 fb                	mov    %edi,%ebx
  402bbb:	85 ff                	test   %edi,%edi
  402bbd:	79 05                	jns    402bc4 <init_timeout+0x10>
  402bbf:	bb 00 00 00 00       	mov    $0x0,%ebx
  402bc4:	be 78 21 40 00       	mov    $0x402178,%esi
  402bc9:	bf 0e 00 00 00       	mov    $0xe,%edi
  402bce:	e8 8d e1 ff ff       	callq  400d60 <signal@plt>
  402bd3:	89 df                	mov    %ebx,%edi
  402bd5:	e8 46 e1 ff ff       	callq  400d20 <alarm@plt>
  402bda:	5b                   	pop    %rbx
  402bdb:	f3 c3                	repz retq 

0000000000402bdd <init_driver>:
  402bdd:	55                   	push   %rbp
  402bde:	53                   	push   %rbx
  402bdf:	48 83 ec 28          	sub    $0x28,%rsp
  402be3:	48 89 fd             	mov    %rdi,%rbp
  402be6:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  402bed:	00 00 
  402bef:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
  402bf4:	31 c0                	xor    %eax,%eax
  402bf6:	be 01 00 00 00       	mov    $0x1,%esi
  402bfb:	bf 0d 00 00 00       	mov    $0xd,%edi
  402c00:	e8 5b e1 ff ff       	callq  400d60 <signal@plt>
  402c05:	be 01 00 00 00       	mov    $0x1,%esi
  402c0a:	bf 1d 00 00 00       	mov    $0x1d,%edi
  402c0f:	e8 4c e1 ff ff       	callq  400d60 <signal@plt>
  402c14:	be 01 00 00 00       	mov    $0x1,%esi
  402c19:	bf 1d 00 00 00       	mov    $0x1d,%edi
  402c1e:	e8 3d e1 ff ff       	callq  400d60 <signal@plt>
  402c23:	ba 00 00 00 00       	mov    $0x0,%edx
  402c28:	be 01 00 00 00       	mov    $0x1,%esi
  402c2d:	bf 02 00 00 00       	mov    $0x2,%edi
  402c32:	e8 59 e2 ff ff       	callq  400e90 <socket@plt>
  402c37:	85 c0                	test   %eax,%eax
  402c39:	79 4f                	jns    402c8a <init_driver+0xad>
  402c3b:	48 b8 45 72 72 6f 72 	movabs $0x43203a726f727245,%rax
  402c42:	3a 20 43 
  402c45:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402c49:	48 b8 6c 69 65 6e 74 	movabs $0x6e7520746e65696c,%rax
  402c50:	20 75 6e 
  402c53:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402c57:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402c5e:	74 6f 20 
  402c61:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402c65:	48 b8 63 72 65 61 74 	movabs $0x7320657461657263,%rax
  402c6c:	65 20 73 
  402c6f:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402c73:	c7 45 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%rbp)
  402c7a:	66 c7 45 24 74 00    	movw   $0x74,0x24(%rbp)
  402c80:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402c85:	e9 2a 01 00 00       	jmpq   402db4 <init_driver+0x1d7>
  402c8a:	89 c3                	mov    %eax,%ebx
  402c8c:	bf 15 37 40 00       	mov    $0x403715,%edi
  402c91:	e8 da e0 ff ff       	callq  400d70 <gethostbyname@plt>
  402c96:	48 85 c0             	test   %rax,%rax
  402c99:	75 68                	jne    402d03 <init_driver+0x126>
  402c9b:	48 b8 45 72 72 6f 72 	movabs $0x44203a726f727245,%rax
  402ca2:	3a 20 44 
  402ca5:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402ca9:	48 b8 4e 53 20 69 73 	movabs $0x6e7520736920534e,%rax
  402cb0:	20 75 6e 
  402cb3:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402cb7:	48 b8 61 62 6c 65 20 	movabs $0x206f7420656c6261,%rax
  402cbe:	74 6f 20 
  402cc1:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402cc5:	48 b8 72 65 73 6f 6c 	movabs $0x2065766c6f736572,%rax
  402ccc:	76 65 20 
  402ccf:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402cd3:	48 b8 73 65 72 76 65 	movabs $0x6120726576726573,%rax
  402cda:	72 20 61 
  402cdd:	48 89 45 20          	mov    %rax,0x20(%rbp)
  402ce1:	c7 45 28 64 64 72 65 	movl   $0x65726464,0x28(%rbp)
  402ce8:	66 c7 45 2c 73 73    	movw   $0x7373,0x2c(%rbp)
  402cee:	c6 45 2e 00          	movb   $0x0,0x2e(%rbp)
  402cf2:	89 df                	mov    %ebx,%edi
  402cf4:	e8 37 e0 ff ff       	callq  400d30 <close@plt>
  402cf9:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402cfe:	e9 b1 00 00 00       	jmpq   402db4 <init_driver+0x1d7>
  402d03:	48 c7 04 24 00 00 00 	movq   $0x0,(%rsp)
  402d0a:	00 
  402d0b:	48 c7 44 24 08 00 00 	movq   $0x0,0x8(%rsp)
  402d12:	00 00 
  402d14:	66 c7 04 24 02 00    	movw   $0x2,(%rsp)
  402d1a:	48 63 50 14          	movslq 0x14(%rax),%rdx
  402d1e:	48 8b 40 18          	mov    0x18(%rax),%rax
  402d22:	48 8b 30             	mov    (%rax),%rsi
  402d25:	48 8d 7c 24 04       	lea    0x4(%rsp),%rdi
  402d2a:	b9 0c 00 00 00       	mov    $0xc,%ecx
  402d2f:	e8 4c e0 ff ff       	callq  400d80 <__memmove_chk@plt>
  402d34:	66 c7 44 24 02 3c 9a 	movw   $0x9a3c,0x2(%rsp)
  402d3b:	ba 10 00 00 00       	mov    $0x10,%edx
  402d40:	48 89 e6             	mov    %rsp,%rsi
  402d43:	89 df                	mov    %ebx,%edi
  402d45:	e8 16 e1 ff ff       	callq  400e60 <connect@plt>
  402d4a:	85 c0                	test   %eax,%eax
  402d4c:	79 50                	jns    402d9e <init_driver+0x1c1>
  402d4e:	48 b8 45 72 72 6f 72 	movabs $0x55203a726f727245,%rax
  402d55:	3a 20 55 
  402d58:	48 89 45 00          	mov    %rax,0x0(%rbp)
  402d5c:	48 b8 6e 61 62 6c 65 	movabs $0x6f7420656c62616e,%rax
  402d63:	20 74 6f 
  402d66:	48 89 45 08          	mov    %rax,0x8(%rbp)
  402d6a:	48 b8 20 63 6f 6e 6e 	movabs $0x7463656e6e6f6320,%rax
  402d71:	65 63 74 
  402d74:	48 89 45 10          	mov    %rax,0x10(%rbp)
  402d78:	48 b8 20 74 6f 20 73 	movabs $0x76726573206f7420,%rax
  402d7f:	65 72 76 
  402d82:	48 89 45 18          	mov    %rax,0x18(%rbp)
  402d86:	66 c7 45 20 65 72    	movw   $0x7265,0x20(%rbp)
  402d8c:	c6 45 22 00          	movb   $0x0,0x22(%rbp)
  402d90:	89 df                	mov    %ebx,%edi
  402d92:	e8 99 df ff ff       	callq  400d30 <close@plt>
  402d97:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  402d9c:	eb 16                	jmp    402db4 <init_driver+0x1d7>
  402d9e:	89 df                	mov    %ebx,%edi
  402da0:	e8 8b df ff ff       	callq  400d30 <close@plt>
  402da5:	66 c7 45 00 4f 4b    	movw   $0x4b4f,0x0(%rbp)
  402dab:	c6 45 02 00          	movb   $0x0,0x2(%rbp)
  402daf:	b8 00 00 00 00       	mov    $0x0,%eax
  402db4:	48 8b 4c 24 18       	mov    0x18(%rsp),%rcx
  402db9:	64 48 33 0c 25 28 00 	xor    %fs:0x28,%rcx
  402dc0:	00 00 
  402dc2:	74 05                	je     402dc9 <init_driver+0x1ec>
  402dc4:	e8 27 df ff ff       	callq  400cf0 <__stack_chk_fail@plt>
  402dc9:	48 83 c4 28          	add    $0x28,%rsp
  402dcd:	5b                   	pop    %rbx
  402dce:	5d                   	pop    %rbp
  402dcf:	c3                   	retq   

0000000000402dd0 <driver_post>:
  402dd0:	53                   	push   %rbx
  402dd1:	4c 89 cb             	mov    %r9,%rbx
  402dd4:	45 85 c0             	test   %r8d,%r8d
  402dd7:	74 27                	je     402e00 <driver_post+0x30>
  402dd9:	48 89 ca             	mov    %rcx,%rdx
  402ddc:	be 2d 37 40 00       	mov    $0x40372d,%esi
  402de1:	bf 01 00 00 00       	mov    $0x1,%edi
  402de6:	b8 00 00 00 00       	mov    $0x0,%eax
  402deb:	e8 10 e0 ff ff       	callq  400e00 <__printf_chk@plt>
  402df0:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  402df5:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  402df9:	b8 00 00 00 00       	mov    $0x0,%eax
  402dfe:	eb 3f                	jmp    402e3f <driver_post+0x6f>
  402e00:	48 85 ff             	test   %rdi,%rdi
  402e03:	74 2c                	je     402e31 <driver_post+0x61>
  402e05:	80 3f 00             	cmpb   $0x0,(%rdi)
  402e08:	74 27                	je     402e31 <driver_post+0x61>
  402e0a:	48 83 ec 08          	sub    $0x8,%rsp
  402e0e:	41 51                	push   %r9
  402e10:	49 89 c9             	mov    %rcx,%r9
  402e13:	49 89 d0             	mov    %rdx,%r8
  402e16:	48 89 f9             	mov    %rdi,%rcx
  402e19:	48 89 f2             	mov    %rsi,%rdx
  402e1c:	be 9a 3c 00 00       	mov    $0x3c9a,%esi
  402e21:	bf 15 37 40 00       	mov    $0x403715,%edi
  402e26:	e8 19 f6 ff ff       	callq  402444 <submitr>
  402e2b:	48 83 c4 10          	add    $0x10,%rsp
  402e2f:	eb 0e                	jmp    402e3f <driver_post+0x6f>
  402e31:	66 c7 03 4f 4b       	movw   $0x4b4f,(%rbx)
  402e36:	c6 43 02 00          	movb   $0x0,0x2(%rbx)
  402e3a:	b8 00 00 00 00       	mov    $0x0,%eax
  402e3f:	5b                   	pop    %rbx
  402e40:	c3                   	retq   

0000000000402e41 <check>:
  402e41:	89 f8                	mov    %edi,%eax
  402e43:	c1 e8 1c             	shr    $0x1c,%eax
  402e46:	85 c0                	test   %eax,%eax
  402e48:	74 1d                	je     402e67 <check+0x26>
  402e4a:	b9 00 00 00 00       	mov    $0x0,%ecx
  402e4f:	eb 0b                	jmp    402e5c <check+0x1b>
  402e51:	89 f8                	mov    %edi,%eax
  402e53:	d3 e8                	shr    %cl,%eax
  402e55:	3c 0a                	cmp    $0xa,%al
  402e57:	74 14                	je     402e6d <check+0x2c>
  402e59:	83 c1 08             	add    $0x8,%ecx
  402e5c:	83 f9 1f             	cmp    $0x1f,%ecx
  402e5f:	7e f0                	jle    402e51 <check+0x10>
  402e61:	b8 01 00 00 00       	mov    $0x1,%eax
  402e66:	c3                   	retq   
  402e67:	b8 00 00 00 00       	mov    $0x0,%eax
  402e6c:	c3                   	retq   
  402e6d:	b8 00 00 00 00       	mov    $0x0,%eax
  402e72:	c3                   	retq   

0000000000402e73 <gencookie>:
  402e73:	53                   	push   %rbx
  402e74:	83 c7 01             	add    $0x1,%edi
  402e77:	e8 24 de ff ff       	callq  400ca0 <srandom@plt>
  402e7c:	e8 3f df ff ff       	callq  400dc0 <random@plt>
  402e81:	89 c3                	mov    %eax,%ebx
  402e83:	89 c7                	mov    %eax,%edi
  402e85:	e8 b7 ff ff ff       	callq  402e41 <check>
  402e8a:	85 c0                	test   %eax,%eax
  402e8c:	74 ee                	je     402e7c <gencookie+0x9>
  402e8e:	89 d8                	mov    %ebx,%eax
  402e90:	5b                   	pop    %rbx
  402e91:	c3                   	retq   
  402e92:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  402e99:	00 00 00 
  402e9c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000402ea0 <__libc_csu_init>:
  402ea0:	41 57                	push   %r15
  402ea2:	41 56                	push   %r14
  402ea4:	41 89 ff             	mov    %edi,%r15d
  402ea7:	41 55                	push   %r13
  402ea9:	41 54                	push   %r12
  402eab:	4c 8d 25 5e 1f 20 00 	lea    0x201f5e(%rip),%r12        # 604e10 <__frame_dummy_init_array_entry>
  402eb2:	55                   	push   %rbp
  402eb3:	48 8d 2d 5e 1f 20 00 	lea    0x201f5e(%rip),%rbp        # 604e18 <__do_global_dtors_aux_fini_array_entry>
  402eba:	53                   	push   %rbx
  402ebb:	49 89 f6             	mov    %rsi,%r14
  402ebe:	49 89 d5             	mov    %rdx,%r13
  402ec1:	4c 29 e5             	sub    %r12,%rbp
  402ec4:	48 83 ec 08          	sub    $0x8,%rsp
  402ec8:	48 c1 fd 03          	sar    $0x3,%rbp
  402ecc:	e8 77 dd ff ff       	callq  400c48 <_init>
  402ed1:	48 85 ed             	test   %rbp,%rbp
  402ed4:	74 20                	je     402ef6 <__libc_csu_init+0x56>
  402ed6:	31 db                	xor    %ebx,%ebx
  402ed8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  402edf:	00 
  402ee0:	4c 89 ea             	mov    %r13,%rdx
  402ee3:	4c 89 f6             	mov    %r14,%rsi
  402ee6:	44 89 ff             	mov    %r15d,%edi
  402ee9:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
  402eed:	48 83 c3 01          	add    $0x1,%rbx
  402ef1:	48 39 eb             	cmp    %rbp,%rbx
  402ef4:	75 ea                	jne    402ee0 <__libc_csu_init+0x40>
  402ef6:	48 83 c4 08          	add    $0x8,%rsp
  402efa:	5b                   	pop    %rbx
  402efb:	5d                   	pop    %rbp
  402efc:	41 5c                	pop    %r12
  402efe:	41 5d                	pop    %r13
  402f00:	41 5e                	pop    %r14
  402f02:	41 5f                	pop    %r15
  402f04:	c3                   	retq   
  402f05:	90                   	nop
  402f06:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  402f0d:	00 00 00 

0000000000402f10 <__libc_csu_fini>:
  402f10:	f3 c3                	repz retq 

Disassembly of section .fini:

0000000000402f14 <_fini>:
  402f14:	48 83 ec 08          	sub    $0x8,%rsp
  402f18:	48 83 c4 08          	add    $0x8,%rsp
  402f1c:	c3                   	retq   
