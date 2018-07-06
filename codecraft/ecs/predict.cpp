#include "bits/stdc++.h"
#include "predict.h"
#include <stdio.h>

int knapsack1(int *Wc, int *Wm, int *V, int *N, int *res, int n, int Cc, int Cm)
{
    int i, j, k, y, count, temp, tem, rw, rm, value = 0;

    int ***f = new int **[16];
    int ***g = new int **[16];
    for (i = 0; i < 16; i++)
    {
        f[i] = new int *[Cc+1];
        g[i] = new int *[Cc+1];
        for (j = 0; j < Cc+1; j++)
        {
            f[i][j] = new int [Cm+1];
            g[i][j] = new int [Cm+1];
        }
    }
    for (k = 0; k < 16; k++)
    {
        for (j = 0; j < Cc+1; j++)
        {
            for (i = 0; i < Cm+1; i++)
            {
                f[k][j][i] = 0;
                g[k][j][i] = 0;
            }
        }
    }

    for(y = 1; y < Cc+1; y++)
    {
        for(j=1; j < Cm+1; j++)
        {
            for(k=1; k < N[0]+1; k++)
            {
                if(k * Wc[0] > y || k * Wm[0] > j)
                {
                    break;
                }
            }
            count = k - 1;
            f[0][y][j] = count * V[0];
            rw = count * Wc[0] / Cc;
            rm = count * Wm[0] / Cm;
            if(rw < rm)
                g[0][y][j] = rw;
            else
                g[0][y][j] = rm;
        }
    }
    for(i = 1; i < n; i++)
    {
        for(y = 1; y < Cc+1; y++)
        {
            for(j=1; j < Cm+1; j++)
            {
                if(y < Wc[i] || j < Wm[i])
                {
                    f[i][y][j] = f[i-1][y][j];
                    g[i][y][j] = g[i-1][y][j];
                }
                else
                {
                    for(k=1; k < N[i]+1; k++)
                    {
                        if(k * Wc[i] > y || k * Wm[i] > j)
                        {
                            break;
                        }
                    }
                    count = k;
                    f[i][y][j] = f[i-1][y][j];
                    g[i][y][j] = g[i-1][y][j];
                    for(k = 1; k < count; k++)
                    {
                        tem = f[i-1][y-Wc[i]*k][j-Wm[i]*k] + k * V[i];
                        rw = k * Wc[i] / Cc;
                        rm = k * Wm[i] / Cm;
                        if(rw < rm)
                            temp = g[i-1][y-Wc[i]*k][j-Wm[i]*k] + rw;
                        else
                            temp = g[i-1][y-Wc[i]*k][j-Wm[i]*k] + rm;
                        if(temp >= g[i][y][j])
                        {
                            f[i][y][j] = tem;
                            g[i][y][j] = temp;
                        }
                    }
                }
            }
        }
    }
    value = f[n-1][Cc][Cm];
//	cout << "value: " << value << endl;
    i = n-1;
    y = Cc;
    j = Cm;
    while(i)
    {
        int count_1 = (N[i] < y/Wc[i]) ? N[i] : y/Wc[i];
        count = (count_1 < j/Wm[i]) ? count_1 : j/Wm[i];
        for(k = count; k > 0; k--)
        {
            if(f[i][y][j] == (f[i-1][y-Wc[i]*k][j-Wm[i]*k] + k*V[i]))
            {
                res[i] = k;
                y = y - k*Wc[i];
                j = j - k*Wm[i];
                break;
            }
        }
        i--;
    }
    res[0] = f[0][y][j]/V[0];
    return value;
}
int knapsack(int *Wc, int *Wm, int *V, int *N, int *res, int n, int Cc, int Cm)
{
    int i, j, k, y, count, temp;
    int value = 0;
    int ***f = new int **[16];
    for (i = 0; i < 16; i++)
    {
        f[i] = new int *[Cc+1];
        for (j = 0; j < Cc+1; j++)
        {
            f[i][j] = new int [Cm+1];
        }
    }
    for (k = 0; k < 16; k++)
    {
        for (j = 0; j < Cc+1; j++)
        {
            for (i = 0; i < Cm+1; i++)
            {
                f[k][j][i] = 0;
            }
        }
    }

    for(y = 1; y < Cc+1; y++)
    {
        for(j=1; j < Cm+1; j++)
        {
            if(N[0] > 0)
            {
                for(k=1; k < N[0]+1; k++)
                {
                    if(k * Wc[0] > y || k * Wm[0] > j)
                    {
                        break;
                    }
                }
                count = k - 1;
                f[0][y][j] = count * V[0];
            }
            else
                f[0][y][j] = 0;
        }
    }
    for(i = 1; i < n; i++)
    {
        for(y = 1; y < Cc+1; y++)
        {
            for(j=1; j < Cm+1; j++)
            {
                if(y < Wc[i] || j < Wm[i])
                {
                    f[i][y][j] = f[i-1][y][j];
                }
                else
                {
                    for(k=1; k < N[i]+1; k++)
                    {
                        if(k * Wc[i] > y || k * Wm[i] > j)
                        {
                            break;
                        }
                    }
                    count = k;
                    f[i][y][j] = f[i-1][y][j];
                    for(k = 1; k < count; k++)
                    {
                        temp = f[i-1][y-Wc[i]*k][j-Wm[i]*k] + k * V[i];
                        if(temp >= f[i][y][j])
                            f[i][y][j] = temp;
                    }
                }
            }
        }
    }
    value = f[n-1][Cc][Cm];
    ///cout << "value: " << value << endl;
    i = n-1;
    y = Cc;
    j = Cm;
    while(i)
    {
        int count_1 = (N[i] < y/Wc[i]) ? N[i] : y/Wc[i];
        count = (count_1 < j/Wm[i]) ? count_1 : j/Wm[i];
        for(k = count; k > 0; k--)
        {
            if(f[i][y][j] == (f[i-1][y-Wc[i]*k][j-Wm[i]*k] + k*V[i]))
            {
                res[i] = k;
                y = y - k*Wc[i];
                j = j - k*Wm[i];
                break;
            }
        }
        i--;
    }
    res[0] = f[0][y][j]/V[0];
    return value;
}


void test(int flavor_demo[][3], int flavor_predict[][2], int allot_flavor[][16], int flavor_number,int numbers, int cpu, int mem, int flag, char * filename)
{
    int i, j, value, num = 0;
	int n = flavor_number;

    int *WC = new int [n];
	int *WM = new int [n];
	int *N = new int [n];
	int *ID = new int [n];

	for(i = 0; i < n; i++)
	{
		ID[i] = flavor_demo[i][0];
		WC[i] = flavor_demo[i][1];
		WM[i] = flavor_demo[i][2];
		for(j = 0; j < n; j++)
		{
			if(ID[i] == flavor_predict[j][0])
			{
				N[i] = flavor_predict[j][1];
			}
		}
	}

	int *V = new int [n];

    if(flag==0)
	    V=WC;
	else
		V=WM;
//
//   for(int i =0;i<n;i++){
//       if(numbers>200){
//         if(flag==0)
//	      V[i]=WC[i];
//	     else
//		  V[i]=WM[i];
//       }
//       else{
//           if(WC[i]>WM[i])
//               V[i]=WC[i];
//           else
//               V[i]=WM[i];
//       }
//   }

//    for(i = 0; i < n; i++)
//    {
//        if(WC[i] > WM[i])
//            V[i] = WC[i];
//        else
//            V[i] = WM[i];
//    }

    int *res = new int[n];
    for(i = 0; i < n; i++)
        res[i] = 0;
    value = knapsack(WC, WM, V, N, res, n, cpu, mem);

	while(value!=0)
	{
		for(i = 0; i < n; i++)
		{
			allot_flavor[num][ID[i]] = res[i];
			N[i] = N[i] - res[i];
			res[i] = 0;
		}
        value = knapsack(WC, WM, V, N, res, n, cpu, mem);
		num++;
	}
    printf("%d\n",num);
    for(int i=0;i<num;i++) {
        for (int j = 0; j < 16; j++) {
            printf("%d  ",allot_flavor[i][j]);
        }
        printf("\n");
    }

    FILE *fp = fopen(filename, "a");
    fprintf(fp,"%d",num);
    fprintf(fp, "\n");
    for(int i=0;i<num;i++){
        fprintf(fp, "%d", i+1);
        for(int j=1;j<16;j++){
            if(allot_flavor[i][j] != 0){
                fprintf(fp, " ");
                fprintf(fp, "flavor");
                fprintf(fp, "%d",j);
                fprintf(fp, " ");
                fprintf(fp, "%d",allot_flavor[i][j]);
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
	//return num;
}



//��Ҫ��ɵĹ��������
void predict_server(char * data[MAX_DATA_NUM],char * info[MAX_INFO_NUM], int data_line_num, int info_line_num ,char * filename)
{
	int days;//训练集天数
	int flavor_number;//flavor种类数
	char *t ="\t";
	char *t1 = " ";
	char *t2 = "-";
	char *p = data[0];//第一条
	p = strtok(p, t);
	p = strtok(NULL, t);
	p = strcpy(p,p+6);
	int flavor0 = atoi(p);
	p = strtok(NULL, t1);
	//p = strcpy(p,p+5);
	p = strtok(p, t2);
	int year = atoi(p);
	printf("%d\n",year);
	p = strtok(NULL, t2);
	int month1 = atoi(p);
    printf("%d\n",month1);
	p = strtok(NULL, t2);
	int day1 = atoi(p);
    printf("%d\n",day1);
	p = data[data_line_num-1];
	p = strtok(p, t);
	p = strtok(NULL, t);
	p = strcpy(p,p+6);
	int flavormax = atoi(p);
	p = strtok(NULL, t1);
	p = strcpy(p,p+5);
	p = strtok(p, t2);
    printf("%d\n",atoi(p));
	if(atoi(p)-month1==0){
		p = strtok(NULL, t2);
		days = atoi(p)-day1+1;
	}
    else if(atoi(p)-month1==1 || (month1==12 && atoi(p)==1)){
	 if(month1 == 1 || month1 == 3 || month1 == 5 || month1 == 7 || month1 == 8 || month1 == 10 || month1 == 12){
		p = strtok(NULL, t2);
		days = 32 - day1 + atoi(p);
	}
	else if(month1 == 4 || month1 == 6 || month1 == 9 || month1 == 11){
		p = strtok(NULL, t2);
		days = 31 - day1 + atoi(p);
	}
	else{	if(year%400 ==0 ||(year%4==0&&year%100!=0))
		{
		p = strtok(NULL, t2);
		days = 30 - day1 + atoi(p);
		}
	else {
		p = strtok(NULL, t2);
		days = 29 - day1 + atoi(p);
	}
    }
	}
    else{
        if(month1==1){
            if(year%400 == 0 ||(year%4 == 0 && year%100 != 0)) {
                p = strtok(NULL, t2);
                days = 32 - day1 + 29 + atoi(p);
            }
            else
            {
                p = strtok(NULL, t2);
                days = 32-day1+28+atoi(p);
            }
        }
        else if(month1==2){
            if(year%400 ==0 ||(year%4==0&&year%100!=0))
            {
                p = strtok(NULL, t2);
                days = 30-day1+31+atoi(p);
            }
            else
            {
                p = strtok(NULL, t2);
                days = 29-day1+31+atoi(p);
            }
        }
        else if(month1==3 || month1==4 || month1==5 || month1==6 || month1==8 || month1==9 || month1==10 || month1==11){
            p = strtok(NULL, t2);
            days = 62-day1+atoi(p);
        }
        else if(month1==7 || month1==12){
            p = strtok(NULL, t2);
            days = 63-day1+atoi(p);
        }
    }

	printf("%d\n\n",days);
	//存储物理资源
	p = strtok(info[0], t1);
	int cpu = atoi(p);//cpu物理量
	p = strtok(NULL, t1);
	int mem = atoi(p);//mem物理量
	printf("%d %d \n",cpu,mem);
//    p = strtok(NULL, t1);
//    int disk = atoi(p);//disk物理量

//处理input中要预测的flavor种类数
	flavor_number = atoi(info[2]);
	int flavor_demo[flavor_number][3];//需要请求的种类demo
	memset(flavor_demo,0,sizeof(flavor_demo));
	printf("%d\n",flavor_number);
	for(int i = 3;i<flavor_number+3;i++){
		p = strtok(info[i], t1);
		p = strcpy(p,p+6);
		flavor_demo[i-3][0] = atoi(p);//flavor
		p = strtok(NULL, t1);
		flavor_demo[i-3][1] = atoi(p);//cpu
		p = strtok(NULL, t1);
		flavor_demo[i-3][2] = atoi(p)/1024;//mem转成GB
	}

	//标记cpu还是mem优化
	int flag = -1;
	if((strcmp(info[flavor_number+4],"CPU\r\n")==0)) flag = 0;//flag=0为cpu优化，1为mem优化
	else flag = 1;
       printf("%s",info[flavor_number+4]);
	printf("%d\n",flag);
	//要求预测时间长度
	int day_length;
	p = strtok(info[flavor_number+6], t1);
	//printf("%s\n",p);
	p = strtok(p, t2);
	//printf("%s\n",p);
	int year_test = atoi(p);
	p = strtok(NULL, t2);

	int month_test = atoi(p);
	//p = strcpy(p, p+8);
    p = strtok(NULL, t2);
    	day_length = atoi(p);
	printf("%d %d %d\n",year_test,month_test,day_length);
	p = strtok(info[flavor_number+7], t1);
	p = strcpy(p, p+8);
	if(day_length<atoi(p)){
    	day_length = atoi(p) - day_length;
	}
    else{
        if(month_test == 1 || month_test == 3 || month_test == 5 || month_test == 7 || month_test == 8 || month_test == 10 || month_test == 12){
            day_length += 31 - day_length + atoi(p);
        }
        else if(month_test == 4 || month_test == 6 || month_test == 9 || month_test == 11){
            day_length += 30 - day_length + atoi(p);
        }
        else{if(year_test%400 ==0 ||(year_test%4==0&&year_test%100!=0))
            {
                day_length += 29 - day_length + atoi(p);
            }
            else {
                day_length += 28 - day_length + atoi(p);
            }

        }

    }
	printf("%d\n",day_length);
//历史数据数组
	int flavor_history[days][16];
	memset(flavor_history,0,sizeof(flavor_history));
	int day2,month2;
	int count=0;
	if(flavor0 <= 15)
		flavor_history[count][flavor0] += 1;
	for(int i=1;i<data_line_num-1;i++){
		p = strtok(data[i], t);
		p = strtok(NULL, t);
		p = strcpy(p,p+6);
		flavor0 = atoi(p);
		// printf("%d\n",flavor0);
		if(flavor0 > 15) continue;
		p = strtok(NULL, t1);
		p = strcpy(p,p+5);
		p = strtok(p, t2);

		month2 = atoi(p);
		p = strtok(NULL, t2);
		day2 = atoi(p);

		if(day1 == day2){
			flavor_history[count][flavor0] += 1;
		}
		else if(day2 > day1){
			count += day2-day1;
			flavor_history[count][flavor0] += 1;
			day1 = day2;
		}
		else{
			if(month1 == 1 || month1 == 3 || month1 == 5 || month1 == 7 || month1 == 8 || month1 == 10 || month1 == 12){
                month1 = month2;
                count += 31 - day1 + day2;
				flavor_history[count][flavor0] += 1;
				day1 = day2;
			}
			else if(month1 == 4 || month1 == 6 || month1 == 9 || month1 == 11){
                month1 = month2;
				count += 30 - day1 + day2;
				flavor_history[count][flavor0] += 1;
				day1 = day2;
			}
			else{
                if(year % 400 == 0 ||(year % 4 == 0 && year % 100 != 0))
		{
                 month1 = month2;
		        count += 29 - day1 + day2;
				flavor_history[count][flavor0] += 1;
				day1 = day2;
		}
	        else {
                month1 = month2;
                count += 28 - day1 + day2;
				flavor_history[count][flavor0] += 1;
				day1 = day2;
	}

			}
		}
	}
	if(flavormax <= 15)
		flavor_history[days-1][flavormax] +=1;

	for(int i=0;i<days;i++) {
		for (int j = 1; j <= 15; j++){
            if(flavor_history[i][j] > 35){
//                flavor_history[i][j] = flavor_history[i-1][j]+2;
//                flavor_history[i][j] = (flavor_history[i-1][j]+ flavor_history[i-2][j])/2 +2;
                flavor_history[i][j] = 0;
                for(int k=0;k<7;k++){
                    flavor_history[i][j] += flavor_history[i-k-1][j];
                }
                flavor_history[i][j] = flavor_history[i][j]/7+2;
            }
			printf("%d ",flavor_history[i][j]);
		}
		printf("\n");
	}
    for(int i=0;i<days;i++) {
        for (int j = 1; j <= 15; j++){
            flavor_history[i][0] += flavor_history[i][j];
        }
        if(flavor_history[i][0]==0){
            for (int j = 1; j <= 15; j++){
                flavor_history[i][j] += flavor_history[i-2][j]*0.3 +flavor_history[i-1][j]*0.7;
            }
        }
        printf("%d   ",flavor_history[i][0]);
    }
    printf("\n\n\n");
//	//从训练集中抽取最后的数据为测试集
	int test_data[16],test_data1[16],test_data2[16];
    float w[16]={2.5,7.5,6.5,7.5,7.5,8.5,10.5,10.5,6.5,9.5,10.5,6.5,7.5,7.5,7.5,6.5};


	memset(test_data,0, sizeof(test_data));
    memset(test_data1,0, sizeof(test_data1));
    memset(test_data2,0, sizeof(test_data2));
    //memset(w,0.0, sizeof(w));

//    for(int i= days-day_length-1;i<days;i++){
      for(int i= 0;i<7;i++){
        for(int j=1;j<=15;j++){
//              test_data1[j] += flavor_history[days-i-1][j];
//              test_data2[j] += flavor_history[days-i-8][j];
            test_data[j] += flavor_history[days-i-1][j];
//            test_data[j] += flavor_history[i-day_length][j]*0.3+flavor_history[i][j]*0.7+0.5;
           // test_data[j] += flavor_history[i][j];
        }
   }
    for(int i=1;i<=15;i++){
        test_data[i] = (test_data[i]*1.0)/7*(day_length*1.0)+w[i];
//        test_data[i] = (test_data2[i]*0.3+test_data1[i]*0.7)/7*(day_length*1.0)+6;
////           test_data[i] += 3;
    }
//    //求参数w,预测
//    for(int i=1;i<=15;i++){
//        printf("%d %d   ",test_data1[i],test_data2[i]);
//        w[i] = (test_data2[i]*1.0)/(test_data1[i]*1.0);
//        printf("%f ",w[i]);
//        test_data[i] = test_data2[i]*w[i];
//        printf("%d   ",test_data[i]);
//    }
//    //求平均
//    for(int i= 0;i<days;i++){
//        for(int j=1;j<=15;j++){
//            test_data[j] += flavor_history[i][j];
//        }
//   }
//    for(int i=1;i<=15;i++){
//        test_data[i] =(int) ((test_data[i]*1.0)/(day_length*1.0)+0.5);
//        printf("%d  ",test_data[i]);
//    }
//    printf("\n");
//    for(int i=1;i<=15;i++){
//        test_data[i] =(int) (((test_data[i]*day_length*1.0)/(days*1.0))+0.5);
//        printf("%d  ",test_data[i]);
//    }
//    printf("\n");
    int predict_flavor[flavor_number][2];
	memset(predict_flavor,0,sizeof(predict_flavor));
    int numbers = 0;
    for(int i=0;i<flavor_number;i++){
        predict_flavor[i][0] = flavor_demo[i][0];
        predict_flavor[i][1] = test_data[flavor_demo[i][0]];
        numbers += predict_flavor[i][1];
        printf("%d  %d  \n",predict_flavor[i][0] , predict_flavor[i][1] );
    }
    printf("%d\n",numbers);

    //剩余训练集训练权重参数


	// ��Ҫ���������
	//char *result_file="";
	//write_result(result_file, filename);
	FILE *fp = fopen(filename, "w");
    fprintf(fp,"%d",numbers);
	fclose(fp);
	fp = fopen(filename,"a");
    fprintf(fp,"\n");
    //char *s ;
    for(int i=0;i<flavor_number;i++) {
         fprintf(fp, "flavor");
        fprintf(fp, "%d", predict_flavor[i][0]);
         fprintf(fp, " ");
         fprintf(fp, "%d", predict_flavor[i][1]);
         fprintf(fp, "\n");
    }
     fprintf(fp, "\n");
    fclose(fp);

    //最优分配
    int allot_flavor[numbers][16];
    memset(allot_flavor,0, sizeof(allot_flavor));
    test(flavor_demo, predict_flavor, allot_flavor, flavor_number,numbers, cpu, mem, flag,filename);
	// ֱ�ӵ�������ļ��ķ��������ָ���ļ���(ps��ע���ʽ����ȷ�ԣ�����н⣬��һ��ֻ��һ�����ݣ��ڶ���Ϊ�գ������п�ʼ���Ǿ�������ݣ�����֮����һ���ո�ָ���)
	//write_result(result_file, filename);
}
