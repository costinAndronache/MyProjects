package view;

import model.ExpressionEvaluator;
import java.awt.EventQueue;

import javax.swing.JFrame;

import java.awt.GridBagLayout;

import javax.swing.JTextField;

import java.awt.GridBagConstraints;
import java.awt.Insets;

import javax.swing.JButton;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;

import javax.swing.JTextArea;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

import model.ExpressionTokenFactory;
import java.awt.Color;

public class View {

	private JFrame frmCjexpressioncalculator;
	private JButton button;
	private JButton button_1;
	private JButton button_2;
	private JButton button_3;
	private JButton button_4;
	private JButton button_5;
	private JButton button_6;
	private JButton button_7;
	private JButton button_8;
	private JButton button_9;
	private JButton button_10;
	private JButton button_11;
	private JButton button_12;
	private JButton button_13;
	private JButton button_14;
	
	private ActionListener1 act1;
	private ActionListener2 act2;
	private JButton btnNewButton_1;
	private JButton button_15;
	private JTextArea textArea;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					View window = new View();
					window.frmCjexpressioncalculator.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public View() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frmCjexpressioncalculator = new JFrame();
		frmCjexpressioncalculator.getContentPane().setForeground(Color.RED);
		frmCjexpressioncalculator.getContentPane().setFont(new Font("Tahoma", Font.PLAIN, 12));
		frmCjexpressioncalculator.setTitle("cJExpressionCalculator");
		frmCjexpressioncalculator.setResizable(false);
		frmCjexpressioncalculator.setAlwaysOnTop(true);
		frmCjexpressioncalculator.setBounds(100, 100, 529, 413);
		frmCjexpressioncalculator.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmCjexpressioncalculator.getContentPane().setLayout(null);
		
		act1 = new ActionListener1();
		act2 = new ActionListener2();
		
		JButton btnNewButton = new JButton("7");
		btnNewButton.setFont(new Font("Tahoma", Font.PLAIN, 17));
		btnNewButton.addActionListener(act1);
		btnNewButton.setBounds(31, 103, 56, 48);
		frmCjexpressioncalculator.getContentPane().add(btnNewButton);
		
		button = new JButton("4");
		button.addActionListener(act1);
		button.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button.setBounds(31, 162, 56, 48);
		frmCjexpressioncalculator.getContentPane().add(button);
		
		button_1 = new JButton("1");
		button_1.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_1.setBounds(31, 221, 56, 48);
		button_1.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_1);
		
		button_2 = new JButton("8");
		button_2.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_2.setBounds(97, 103, 56, 48);
		button_2.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_2);
		
		button_3 = new JButton("5");
		button_3.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_3.setBounds(97, 162, 56, 48);
		button_3.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_3);
		
		button_4 = new JButton("2");
		button_4.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_4.setBounds(97, 221, 56, 48);
		button_4.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_4);
		
		button_5 = new JButton("9");
		button_5.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_5.setBounds(163, 103, 56, 48);
		button_5.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_5);
		
		button_6 = new JButton("6");
		button_6.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_6.setBounds(163, 162, 56, 48);
		button_6.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_6);
		
		button_7 = new JButton("3");
		button_7.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_7.setBounds(163, 221, 56, 48);
		button_7.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_7);
		
		button_8 = new JButton("/");
		button_8.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_8.setBounds(229, 103, 56, 48);
		button_8.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_8);
		
		button_9 = new JButton("*");
		button_9.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_9.setBounds(229, 162, 56, 48);
		button_9.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_9);
		
		button_10 = new JButton("-");
		button_10.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_10.setBounds(229, 221, 56, 48);
		button_10.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_10);
		
		button_11 = new JButton("+");
		button_11.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_11.setBounds(229, 280, 56, 48);
		button_11.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_11);
		
		button_12 = new JButton("=");
		button_12.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_12.setBounds(163, 280, 56, 48);
		
		button_12.addActionListener(new ActionListener()
		{
			ExpressionEvaluator ev = new ExpressionEvaluator();
			
			public void actionPerformed(ActionEvent e)
			{
				try
				{
				String result = " " + ev.evaluateExpression(textArea.getText());
				
				textArea.setText(result);
			}
				catch(Exception ex)
				{
					textArea.setText("Errors in expression:" +" " + textArea.getText());
				}
			
		}
		});
		frmCjexpressioncalculator.getContentPane().add(button_12);
		
		button_13 = new JButton("0");
		button_13.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_13.setBounds(31, 280, 56, 48);
		button_13.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_13);
		
		button_14 = new JButton(".");
		button_14.setFont(new Font("Tahoma", Font.PLAIN, 17));
		button_14.setBounds(97, 280, 56, 48);
		button_14.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_14);
		
		btnNewButton_1 = new JButton("(");
		btnNewButton_1.setBounds(295, 103, 39, 33);
		btnNewButton_1.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(btnNewButton_1);
		
		button_15 = new JButton(")");
		button_15.setBounds(344, 103, 39, 33);
		button_15.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_15);
		
		textArea = new JTextArea();
		textArea.setFont(new Font("Lucida Console", Font.PLAIN, 14));
		textArea.setLineWrap(true);
		textArea.setBounds(32, 44, 436, 48);
		frmCjexpressioncalculator.getContentPane().add(textArea);
		
		JLabel lblNewLabel = new JLabel("cJExpressionCalculator");
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setFont(new Font("Consolas", Font.BOLD, 15));
		lblNewLabel.setBounds(133, 0, 235, 33);
		frmCjexpressioncalculator.getContentPane().add(lblNewLabel);
		
		JButton btnNewButton_2 = new JButton("log");
		btnNewButton_2.setBounds(295, 162, 56, 48);
		btnNewButton_2.addActionListener(act2);
		frmCjexpressioncalculator.getContentPane().add(btnNewButton_2);
		
		JButton btnSqrt = new JButton("sqrt");
		btnSqrt.setFont(new Font("Tahoma", Font.PLAIN, 10));
		btnSqrt.setBounds(361, 162, 56, 48);
		btnSqrt.addActionListener(act2);
		frmCjexpressioncalculator.getContentPane().add(btnSqrt);
		
		JButton btnPow = new JButton("pow");
		btnPow.setFont(new Font("Tahoma", Font.PLAIN, 10));
		btnPow.addActionListener(act2);
		btnPow.setBounds(427, 162, 56, 48);
		frmCjexpressioncalculator.getContentPane().add(btnPow);
		
		JButton btnSin = new JButton("sin");
		btnSin.setBounds(295, 221, 56, 48);
		btnSin.addActionListener(act2);
		frmCjexpressioncalculator.getContentPane().add(btnSin);
		
		JButton btnCos = new JButton("cos");
		btnCos.setBounds(361, 221, 56, 48);
		btnCos.addActionListener(act2);
		frmCjexpressioncalculator.getContentPane().add(btnCos);
		
		JButton btnTg = new JButton("tan");
		btnTg.setBounds(427, 221, 56, 48);
		btnTg.addActionListener(act2);
		frmCjexpressioncalculator.getContentPane().add(btnTg);
		
		JButton btnMod = new JButton("%");
		btnMod.setBounds(295, 280, 56, 48);
		btnMod.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(btnMod);
		
		JButton btnFactorial = new JButton("fact");
		btnFactorial.setFont(new Font("Tahoma", Font.PLAIN, 12));
		btnFactorial.addActionListener(act2);
		btnFactorial.setBounds(361, 280, 56, 48);
		frmCjexpressioncalculator.getContentPane().add(btnFactorial);
		
		JButton btnLn = new JButton("ln");
		btnLn.setBounds(427, 280, 56, 48);
		btnLn.addActionListener(act2);
		frmCjexpressioncalculator.getContentPane().add(btnLn);
		
		JButton button_16 = new JButton(",");
		button_16.setBounds(393, 103, 39, 33);
		button_16.addActionListener(act1);
		frmCjexpressioncalculator.getContentPane().add(button_16);
		
		JButton btnCe = new JButton("CE");
		btnCe.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				textArea.setText("");
				textArea.requestFocus();
			}
		});
		btnCe.setForeground(Color.RED);
		btnCe.setFont(new Font("Tahoma", Font.PLAIN, 10));
		btnCe.setBounds(442, 103, 56, 33);
	
		frmCjexpressioncalculator.getContentPane().add(btnCe);
		
		JTextArea txtrAuthorAndronacheCostin = new JTextArea();
		txtrAuthorAndronacheCostin.setFont(new Font("Lucida Sans", Font.PLAIN, 11));
		txtrAuthorAndronacheCostin.setLineWrap(true);
		txtrAuthorAndronacheCostin.setEditable(false);
		txtrAuthorAndronacheCostin.setText("Author: Andronache Costin    InfoUAIC , IB7");
		txtrAuthorAndronacheCostin.setBounds(361, 339, 152, 38);
		frmCjexpressioncalculator.getContentPane().add(txtrAuthorAndronacheCostin);
	}
	
	private class ActionListener1 implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			JButton source = (JButton)e.getSource();
			String currentText = textArea.getText();
			int pos = textArea.getCaretPosition();
			
			if(pos<currentText.length())
			{
			
			
			String left = currentText.substring(0, pos);
			String right = currentText.substring(pos);
			
			
			
			textArea.setText(left + source.getText() + right);
			textArea.setCaretPosition(pos+1);
			
		}
			else
				textArea.setText(textArea.getText() + source.getText());
			
			textArea.requestFocus();
		}
	}
	
	private class ActionListener2 implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			JButton source = (JButton)e.getSource();
			String currentText = textArea.getText();
			int pos = textArea.getCaretPosition();
			
			if(pos<currentText.length())
			{
			
			
			String left = currentText.substring(0, pos);
			String right = currentText.substring(pos);
			
			
			
			textArea.setText(left + source.getText()+"( )" + right);
			textArea.setCaretPosition(pos+5);
			
		}
			else
				{
				textArea.setText(textArea.getText() + source.getText() + "( )");
				textArea.setCaretPosition(textArea.getCaretPosition()-1);
				}
			
			textArea.requestFocus();
		}
	}
}
