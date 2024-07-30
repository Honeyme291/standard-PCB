#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
int main(int argc, char **argv) {
  pairing_t pairing;
  double t0, t1;
  element_t Smk,P,Ppub,XS,YS,xS,yS,uS,XR,YR,xR,yR,uR,t,k,T,K,sign,Z,h1,h2,h3,h4,h5,tmp1,tmp2,tmp3,tmp4,Q,Q1,option,option1,option2;
  pbc_demo_pairing_init(pairing, argc, argv);
  if (!pairing_is_symmetric(pairing)) pbc_die("pairing must be symmetric");
  
  //初始化参数。
  element_init_Zr(Smk,pairing);
  
  element_init_Zr(xS,pairing);
  element_init_Zr(uS,pairing);
  element_init_Zr(yS,pairing);
  
  element_init_Zr(xR,pairing);
  element_init_Zr(yR,pairing);
  element_init_Zr(uR,pairing);
  
  element_init_Zr(t,pairing);
  element_init_Zr(k,pairing);
  
  element_init_Zr(option1,pairing);
  element_init_Zr(option2,pairing);
  
  
  element_init_G1(P,pairing);
  element_init_G1(Ppub,pairing);
  element_init_G1(XS,pairing);
  element_init_G1(YS,pairing);
  element_init_G1(XR,pairing);
  element_init_G1(YR,pairing);
  element_init_G1(T,pairing);
  element_init_G1(K,pairing);
  element_init_G1(Z,pairing);
  element_init_Zr(sign,pairing);
  
  element_init_G1(h1, pairing);
  element_init_G1(h2, pairing);
  element_init_G1(h3, pairing);
  element_init_G1(h4, pairing);
  element_init_G1(h5, pairing);
  element_init_G1(Q, pairing);
  element_init_G1(Q1,pairing);
  
  element_init_G1(tmp1,pairing);
  
  element_init_G1(tmp2,pairing);
  
  element_init_G1(tmp3,pairing);
  
  element_init_G1(tmp4,pairing);
  element_init_G1(Q,pairing);
  
  element_init_G1(Q1,pairing);
  
  element_init_G1(option,pairing);
   t0 = pbc_get_time();
   //首先经历setup阶段.
  printf("Setup Phase-----\n");
  
  element_random(P);
  element_printf("P = %B\n", P);
  element_random(Smk);
  element_mul_zn(Ppub, P, Smk);
  element_printf("Ppub = %B\n", Ppub);
  
  printf("EXTRACT STAGE\n");
  //发送者S注册.
  printf("Sender Register-----\n");
  element_random(xS);
  element_mul_zn(XS,P,xS);
  element_random(uS);
  element_mul_zn(YS,P,uS);
  element_add(yS,uS,Smk);
  element_printf("XS = %B\n", XS);
  element_printf("YS = %B\n", YS);
  
  //接收者R注册.
  printf("Receiver Register-----\n");
  element_random(xR);
  element_mul_zn(XR,P,xR);
  element_random(uR);
  element_mul_zn(YR,P,uR);
  element_add(yR,uR,Smk);
  element_printf("XR = %B\n", XR);
  element_printf("YR = %B\n", YR);
  
  
  //发送消息
  printf("Sender send to Receiver -----\n");
  
  element_random(k);
  
  element_random(t);
  
  element_mul_zn(K,P,k);
  element_mul_zn(T,P,t);
  
  element_add(tmp1,XR,YR);
  
  element_add(tmp2,tmp1,Ppub);
  
  element_mul_zn(tmp3,tmp2,k);
  
  
  element_add(tmp1,YR,Ppub);
  
  element_mul_zn(tmp4,tmp1,t);
  
  element_add(Q,tmp4,tmp3);
  
  element_add(option1,t,xS);
  
  element_add(sign,option1,yS);
  
  
  element_printf("Q = %B\n", Q);
  element_printf("sign = %B\n", sign);
  element_printf("T = %B\n", T);
  element_printf("K = %B\n", K);
  
  
  //接收阶段
  printf("Decryption Phase -----\n");
  
  element_add(option1,xR,yR);
  
  element_mul_zn(tmp2,K,option1);
  
  element_mul_zn(tmp3,T,yR);
  
  element_add(Q1,tmp2,tmp3);
  
  element_printf("Q1 = %B\n", Q1);
 
  if (element_cmp(Q, Q1))
    printf("Decryption Success. Start session...\n");
  else
    printf("Decryption fail. Try again, please.\n");
	
  //验证阶段
  printf("Verification Phase -----\n");
  
  element_mul_zn(tmp1,P,sign);
  
  element_add(tmp4,YS,Ppub);
  
  element_add(option,T,tmp4);
  
  element_add(option,option,XS);
  
  if (element_cmp(option, tmp1))
    printf("Verify Success. Start session...\n");
  else
    printf("Verify fail. Try again, please.\n");


	
	
	element_clear(K);
	element_clear(T);
	
	element_clear(h1);
	element_clear(h2);
	element_clear(h3);
	element_clear(h4);
	element_clear(h5);
	element_clear(Smk);
	element_clear(P);
	element_clear(Ppub);
	element_clear(XS);
	element_clear(YS);
	element_clear(xS);
	element_clear(yS);
	element_clear(uS);
    element_clear(XR);
	element_clear(YR);
	element_clear(xR);
	element_clear(yR);
	element_clear(uR);
	
	element_clear(t);
	element_clear(k);
	element_clear(sign);
	element_clear(Z);
	
	element_clear(tmp1);
	element_clear(tmp2);
	element_clear(tmp3);
	element_clear(tmp4);
	element_clear(Q);
	element_clear(Q1);
	element_clear(option);
	
	t1 = pbc_get_time();
	printf("All time = %fs\n", t1 - t0);
	printf("Have Good day.\n");
	return 0;
  
 }