package com.chen.chessBoard;


import java.awt.Image;
import java.awt.Toolkit;

import javax.swing.ImageIcon;

import com.chen.whindow.ChineseChessMainFrame;


public class ChessPieces {
	public String name;
	/**
	 * 0£ººÚ½«
	 * 1£ººÚ³µ
	 * 2£ººÚÂí
	 * 3£ººÚÅÚ
	 * 4£ººÚÊ¿
	 * 5£ººÚÏà
	 * 6£ººÚ×ä
	 * 7£ººì±ø
	 * 8£ººì³µ
	 * 9£ººìÂí
	 * 10£ººìÅÚ
	 * 11£ººìÊ¿
	 * 12£ººìË§
	 * 13£ººìÏó
	 */
	public int id;
	public Image Icon;
	
	public ChessPieces(int Id){
		this.id = Id;
		String FileName = null;
		if (this.id == 0){
			this.name = new String("ºÚ½«");
			FileName = new String("black-jiang");
		}
		else if (this.id == 1){
			this.name = new String("ºÚ³µ");
			FileName = new String("black-ju");
		}
		else if (this.id == 2){
			this.name = new String("ºÚÂí");
			FileName = new String("black-ma");
		}
		else if (this.id == 3){
			this.name = new String("ºÚÅÚ");
			FileName = new String("black-pao");
		}
		else if (this.id == 4){
			this.name = new String("ºÚÊ¿");
			FileName = new String("black-shi");
		}
		else if (this.id == 5){
			this.name = new String("ºÚÏó");
			FileName = new String("black-xiang");
		}
		else if (this.id == 6){
			this.name = new String("ºÚ×ä");
			FileName = new String("black-zu");
		}
		else if (this.id == 7){
			this.name = new String("ºì±ø");
			FileName = new String("red-bing");
		}
		else if (this.id == 8){
			this.name = new String("ºì³µ");
			FileName = new String("red-ju");
		}
		else if (this.id == 9){
			this.name = new String("ºìÂí");
			FileName = new String("red-ma");
		}
		else if (this.id == 10){
			this.name = new String("ºìÅÚ");
			FileName = new String("red-pao");
		}
		else if (this.id == 11){
			this.name = new String("ºìÊ¿");
			FileName = new String("red-shi");
		}
		else if (this.id == 12){
			this.name = new String("ºìË§");
			FileName = new String("red-shuai");
		}
		else if (this.id == 13){
			this.name = new String("ºìÏà");
			FileName = new String("red-xiang");
		}
		
		//ÉèÖÃImageIcon
		this.Icon = Toolkit.getDefaultToolkit().getImage(ChineseChessMainFrame.class.getResource("/imageLibary/" + FileName + ".png"));
	}
}
