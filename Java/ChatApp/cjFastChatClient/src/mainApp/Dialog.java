package mainApp;

import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTextField;
import javax.swing.BoxLayout;
import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.JLabel;
import javax.swing.SwingConstants;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;

public class Dialog extends JDialog {

	private final JPanel contentPanel = new JPanel();
	private JTextField tfIpAddress;
	private JTextField tfPort;
	private JTextField tfUsername;
	
	MainApp mainApp;
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		try {
			Dialog dialog = new Dialog();
			dialog.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			dialog.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Create the dialog.
	 */
	public Dialog() {
		setBounds(100, 100, 503, 232);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		{
			tfIpAddress = new JTextField();
			tfIpAddress.setBounds(177, 79, 119, 20);
			tfIpAddress.setColumns(10);
		}
		contentPanel.setLayout(null);
		contentPanel.add(tfIpAddress);
		
		tfPort = new JTextField();
		tfPort.setColumns(10);
		tfPort.setBounds(177, 110, 119, 20);
		contentPanel.add(tfPort);
		
		tfUsername = new JTextField();
		tfUsername.setColumns(10);
		tfUsername.setBounds(177, 141, 119, 20);
		contentPanel.add(tfUsername);
		
		JLabel lblHelloAndWelcome = new JLabel("Hello and welcome to cjFastChat");
		lblHelloAndWelcome.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblHelloAndWelcome.setHorizontalAlignment(SwingConstants.CENTER);
		lblHelloAndWelcome.setBounds(110, 0, 238, 20);
		contentPanel.add(lblHelloAndWelcome);
		
		JLabel lblFirstinsertTheServers = new JLabel("First, insert the server's address and port. The host user will give them to you.");
		lblFirstinsertTheServers.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblFirstinsertTheServers.setBounds(10, 23, 475, 20);
		contentPanel.add(lblFirstinsertTheServers);
		
		JLabel lblThenInsertYour = new JLabel("Then, insert your desired username and hit ok.");
		lblThenInsertYour.setFont(new Font("Tahoma", Font.BOLD, 11));
		lblThenInsertYour.setHorizontalAlignment(SwingConstants.CENTER);
		lblThenInsertYour.setBounds(37, 42, 387, 20);
		contentPanel.add(lblThenInsertYour);
		
		JLabel lblIpAddress = new JLabel("IP address");
		lblIpAddress.setHorizontalAlignment(SwingConstants.CENTER);
		lblIpAddress.setBounds(63, 79, 104, 20);
		contentPanel.add(lblIpAddress);
		
		JLabel lblPort = new JLabel("Port");
		lblPort.setBounds(120, 127, -66, -23);
		contentPanel.add(lblPort);
		
		JLabel lblPort_1 = new JLabel("Port");
		lblPort_1.setHorizontalAlignment(SwingConstants.CENTER);
		lblPort_1.setBounds(73, 110, 94, 20);
		contentPanel.add(lblPort_1);
		
		JLabel lblDesiredUsername = new JLabel("Desired username");
		lblDesiredUsername.setBounds(37, 141, 130, 20);
		contentPanel.add(lblDesiredUsername);
		{
			JPanel buttonPane = new JPanel();
			getContentPane().add(buttonPane, BorderLayout.SOUTH);
			buttonPane.setLayout(new FlowLayout());
			{
				JButton okButton = new JButton("OK");
				okButton.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent arg0) {
						
						mainApp.receiveParameters(tfIpAddress.getText(),Integer.parseInt(tfPort.getText()), tfUsername.getText());
						
					}
				});
				okButton.setBounds(321, 5, 49, 23);
				okButton.setActionCommand("OK");
				buttonPane.add(okButton);
				getRootPane().setDefaultButton(okButton);
			}
			{
				JButton cancelButton = new JButton("Cancel");
				cancelButton.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent arg0) {
						System.exit(0);
					}
				});
				cancelButton.setBounds(375, 5, 67, 23);
				cancelButton.setActionCommand("Cancel");
				buttonPane.add(cancelButton);
			}
		}
	}
	
	public void setMainApp(MainApp mainApp)
	{
		this.mainApp=mainApp;
	}
}
