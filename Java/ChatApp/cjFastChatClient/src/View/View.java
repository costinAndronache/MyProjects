package View;

import java.awt.EventQueue;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollBar;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

import cjFastChatClient.AppModel;
import cjFastChatClient.AppModelListener;
import cjFastChatCommon.SvUserMessage;
import cjFastChatCommon.UserLogin;

public class View extends JFrame implements AppModelListener {

	private JPanel contentPane;
	private JTextField textField;
	JTextArea textArea;
	JButton btnNewButton;
	JScrollPane scrollPane;
	
	AppModel appModel;
	NewLoginDialog nd;
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					View frame = new View();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public View() {
		setTitle("cjFastChatClient");
		setResizable(false);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 546, 410);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(null);
		setContentPane(contentPane);
		
		
		
		textArea = new JTextArea();
		textArea.setWrapStyleWord(true);
		textArea.setEditable(false);
		textArea.setBounds(10, 11, 459, 312);
		
		scrollPane = new JScrollPane(textArea);
		scrollPane.setBounds(0,0,470,320);
		

		
		contentPane.add(scrollPane);
		
		textField = new JTextField();
		textField.setBounds(10, 334, 459, 23);
		contentPane.add(textField);
		textField.setColumns(10);
		
		btnNewButton = new JButton();
		btnNewButton.setFont(new Font("Tahoma", Font.BOLD, 9));
		btnNewButton.setText("Send");
		btnNewButton.setHorizontalAlignment(SwingConstants.LEFT);
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				String userInput = textField.getText();
				
				if(userInput.length()>0)
				{
					appModel.sendMessage(userInput);
					JScrollBar sb = scrollPane.getVerticalScrollBar();
					
					sb.setValue(sb.getMaximum());
					textField.setText("");
					textField.requestFocus();
				}
			}
		});
		
		btnNewButton.setBounds(471, 334, 59, 23);
		contentPane.add(btnNewButton);
		
		textField.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				String userInput = textField.getText();
				
				if(userInput.length()>0)
				{
					appModel.sendMessage(userInput);
					JScrollBar sb = scrollPane.getVerticalScrollBar();
					
					sb.setValue(sb.getMaximum());
					
					textField.setText("");
				}
			}
		});
		//setVisible(true);
	}
	
	@Override
	public void loginOk()
	{
		setVisible(true);
	}
	
	@Override
	public void messageReceived(SvUserMessage message)
	{
		textArea.append(message.userID()+ " : " + message.userMessage() + '\n');
	}
	
	@Override
	public void needNewLogin()
	{
		System.out.println("It appears we need a new login.");
		nd= new NewLoginDialog();
		nd.setView(this);
		nd.setVisible(true);
	}
	
	public void setAppModel(AppModel appModel)
	{
		this.appModel=appModel;
		
	}
	
	public void newLoginReady(String newID)
	{
		nd.setVisible(false);
		appModel.makeLoginRequest(new UserLogin(newID));
	}
	
}
