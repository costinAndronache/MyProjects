package View;

import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JTextField;

public class NewLoginDialog extends JDialog {

	private final JPanel contentPanel = new JPanel();
	private JTextField textField;
	View view;
	
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		try {
			NewLoginDialog dialog = new NewLoginDialog();
			dialog.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			dialog.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Create the dialog.
	 */
	public NewLoginDialog() {
		setBounds(100, 100, 327, 117);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		JLabel lblItAppearsThat = new JLabel("It appears that username is allready in use.");
		lblItAppearsThat.setBounds(10, 11, 260, 19);
		contentPanel.add(lblItAppearsThat);
		
		JLabel lblTryANew = new JLabel("Try a new one: ");
		lblTryANew.setBounds(10, 32, 149, 25);
		contentPanel.add(lblTryANew);
		
		textField = new JTextField();
		textField.setBounds(105, 34, 136, 23);
		contentPanel.add(textField);
		textField.setColumns(10);
		{
			JPanel buttonPane = new JPanel();
			buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
			getContentPane().add(buttonPane, BorderLayout.SOUTH);
			{
				JButton okButton = new JButton("OK");
				okButton.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						view.newLoginReady(textField.getText());
					}
				});
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
				cancelButton.setActionCommand("Cancel");
				buttonPane.add(cancelButton);
			}
		}
	}
	
	public void setView(View view)
	{
		this.view=view;
	}
	

	
}
