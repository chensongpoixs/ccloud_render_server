package com.chen.whindow;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

/**
 * ������ʾ��Ϣ���࣬��ʾlog�е����10��

 * @time 20141127
 *
 */
public class InformationBoard extends JPanel{
	//��¼����
	StringBuffer log = new StringBuffer();
	//���ڴ������10��
	String[] logS = new String[10];
	//Add�����Ĳ���λ��
	int Address = 0;
	
	public InformationBoard(){
		super();
		//���ý���͸��
		this.setOpaque(false);
		//��ʼ����ʾ��10��
		for (int i = 0;i < 10; i ++){
			logS[i] = new String("");
		}
		//���ò���λ��Ϊ��0��
		Address = 0;
	}
	public void paintComponent(Graphics g){
		//����һ���յ�ͼƬ��
		BufferedImage BImage = new BufferedImage(this.getWidth(),this.getHeight(),BufferedImage.TYPE_INT_ARGB);
		//��ȡͼƬ����Graphics
		Graphics2D g2d = BImage.createGraphics();
		//���Ʊ���ͼƬ
		g2d.drawImage(Toolkit.getDefaultToolkit().getImage(ChineseChessMainFrame.class.getResource("/imageLibary/InfBoard.png")), 0, 0,this);
		//����������ɫ
		g2d.setColor(Color.white);
		//��������
		g2d.setFont(new Font("�����п�",Font.CENTER_BASELINE,28));
		//�������忹���
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		//�������壬����Ϊ��Ҫ��ʾ��10������
		for (int i = 0;i < 10;i ++){
			g2d.drawString(logS[i], 100, 60 + i * 40);
		}
		//ˢ��ͼƬ����g
		g.drawImage(BImage, 0, 0, null);
	}
	
	public String AddLog(String s){
		//��¼���ݺ����һ��
		log.append(s + "\n");
		//ԭ��¼С��10�еĴ���
		if (Address < 10){
			logS[Address] = s;
			Address ++;
		}
		//ԭ��¼���ڵ���10�еĴ���
		else{
			for (int i = 0;i < 9;i ++){
				logS[i] = logS[i + 1];
			}
			logS[9] = s;
		}
		//ˢ�½���
		this.paintImmediately(0, 0, this.getWidth(), this.getHeight());
		return new String(log);
	}
	
	public void Clear(){
		//���log
		this.log = new StringBuffer();
		//�����ʾ��10��
		for (int i = 0;i < 10; i ++){
			logS[i] = new String("");
		}
		//��ղ���λ��
		Address = 0;
	}
}
