namespace Games.BlackjackClient
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.buttonHit = new System.Windows.Forms.Button();
            this.buttonStay = new System.Windows.Forms.Button();
            this.buttonJoin = new System.Windows.Forms.Button();
            this.buttonStart = new System.Windows.Forms.Button();
            this.listBoxHistory = new System.Windows.Forms.ListBox();
            this.listBoxCards = new System.Windows.Forms.ListBox();
            this.labelValue = new System.Windows.Forms.Label();
            this.labelTurn = new System.Windows.Forms.Label();
            this.buttonEvaluate = new System.Windows.Forms.Button();
            this.labelCurrentState = new System.Windows.Forms.Label();
            this.listBoxDealer = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.labelDealter = new System.Windows.Forms.Label();
            this.textBoxChat = new System.Windows.Forms.TextBox();
            this.buttonChat = new System.Windows.Forms.Button();
            this.labelEmotivState = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonHit
            // 
            this.buttonHit.Location = new System.Drawing.Point(34, 220);
            this.buttonHit.Name = "buttonHit";
            this.buttonHit.Size = new System.Drawing.Size(75, 23);
            this.buttonHit.TabIndex = 0;
            this.buttonHit.Text = "Hit/Left";
            this.buttonHit.UseVisualStyleBackColor = true;
            this.buttonHit.Click += new System.EventHandler(this.buttonHit_Click);
            // 
            // buttonStay
            // 
            this.buttonStay.Location = new System.Drawing.Point(139, 220);
            this.buttonStay.Name = "buttonStay";
            this.buttonStay.Size = new System.Drawing.Size(75, 23);
            this.buttonStay.TabIndex = 1;
            this.buttonStay.Text = "Stay/Push";
            this.buttonStay.UseVisualStyleBackColor = true;
            this.buttonStay.Click += new System.EventHandler(this.buttonStay_Click);
            // 
            // buttonJoin
            // 
            this.buttonJoin.Enabled = false;
            this.buttonJoin.Location = new System.Drawing.Point(395, 9);
            this.buttonJoin.Name = "buttonJoin";
            this.buttonJoin.Size = new System.Drawing.Size(75, 23);
            this.buttonJoin.TabIndex = 2;
            this.buttonJoin.Text = "Join";
            this.buttonJoin.UseVisualStyleBackColor = true;
            this.buttonJoin.Visible = false;
            this.buttonJoin.Click += new System.EventHandler(this.buttonJoin_Click);
            // 
            // buttonStart
            // 
            this.buttonStart.Enabled = false;
            this.buttonStart.Location = new System.Drawing.Point(250, 220);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(75, 23);
            this.buttonStart.TabIndex = 3;
            this.buttonStart.Text = "ReStart";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // listBoxHistory
            // 
            this.listBoxHistory.FormattingEnabled = true;
            this.listBoxHistory.Location = new System.Drawing.Point(476, 23);
            this.listBoxHistory.Name = "listBoxHistory";
            this.listBoxHistory.Size = new System.Drawing.Size(349, 238);
            this.listBoxHistory.TabIndex = 4;
            // 
            // listBoxCards
            // 
            this.listBoxCards.FormattingEnabled = true;
            this.listBoxCards.Location = new System.Drawing.Point(34, 25);
            this.listBoxCards.Name = "listBoxCards";
            this.listBoxCards.Size = new System.Drawing.Size(365, 82);
            this.listBoxCards.TabIndex = 5;
            // 
            // labelValue
            // 
            this.labelValue.AutoSize = true;
            this.labelValue.Location = new System.Drawing.Point(59, 9);
            this.labelValue.Name = "labelValue";
            this.labelValue.Size = new System.Drawing.Size(0, 13);
            this.labelValue.TabIndex = 6;
            // 
            // labelTurn
            // 
            this.labelTurn.AutoSize = true;
            this.labelTurn.Location = new System.Drawing.Point(214, 23);
            this.labelTurn.Name = "labelTurn";
            this.labelTurn.Size = new System.Drawing.Size(0, 13);
            this.labelTurn.TabIndex = 7;
            // 
            // buttonEvaluate
            // 
            this.buttonEvaluate.Enabled = false;
            this.buttonEvaluate.Location = new System.Drawing.Point(405, 38);
            this.buttonEvaluate.Name = "buttonEvaluate";
            this.buttonEvaluate.Size = new System.Drawing.Size(75, 23);
            this.buttonEvaluate.TabIndex = 8;
            this.buttonEvaluate.Text = "Evaluate";
            this.buttonEvaluate.UseVisualStyleBackColor = true;
            this.buttonEvaluate.Visible = false;
            this.buttonEvaluate.Click += new System.EventHandler(this.buttonEvaluate_Click);
            // 
            // labelCurrentState
            // 
            this.labelCurrentState.AutoSize = true;
            this.labelCurrentState.Location = new System.Drawing.Point(278, 250);
            this.labelCurrentState.Name = "labelCurrentState";
            this.labelCurrentState.Size = new System.Drawing.Size(0, 13);
            this.labelCurrentState.TabIndex = 9;
            // 
            // listBoxDealer
            // 
            this.listBoxDealer.FormattingEnabled = true;
            this.listBoxDealer.Location = new System.Drawing.Point(34, 132);
            this.listBoxDealer.Name = "listBoxDealer";
            this.listBoxDealer.Size = new System.Drawing.Size(365, 82);
            this.listBoxDealer.TabIndex = 10;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 13);
            this.label1.TabIndex = 11;
            this.label1.Text = "Yours:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 116);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 15;
            this.label2.Text = "Dealers";
            // 
            // labelDealter
            // 
            this.labelDealter.AutoSize = true;
            this.labelDealter.Location = new System.Drawing.Point(59, 116);
            this.labelDealter.Name = "labelDealter";
            this.labelDealter.Size = new System.Drawing.Size(0, 13);
            this.labelDealter.TabIndex = 14;
            // 
            // textBoxChat
            // 
            this.textBoxChat.Location = new System.Drawing.Point(476, 271);
            this.textBoxChat.Name = "textBoxChat";
            this.textBoxChat.Size = new System.Drawing.Size(295, 20);
            this.textBoxChat.TabIndex = 16;
            this.textBoxChat.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxChat_KeyPress);
            // 
            // buttonChat
            // 
            this.buttonChat.Location = new System.Drawing.Point(778, 271);
            this.buttonChat.Name = "buttonChat";
            this.buttonChat.Size = new System.Drawing.Size(53, 23);
            this.buttonChat.TabIndex = 17;
            this.buttonChat.Text = "Chat";
            this.buttonChat.UseVisualStyleBackColor = true;
            this.buttonChat.Click += new System.EventHandler(this.buttonChat_Click);
            // 
            // labelEmotivState
            // 
            this.labelEmotivState.AutoSize = true;
            this.labelEmotivState.Location = new System.Drawing.Point(139, 286);
            this.labelEmotivState.Name = "labelEmotivState";
            this.labelEmotivState.Size = new System.Drawing.Size(0, 13);
            this.labelEmotivState.TabIndex = 18;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(837, 303);
            this.Controls.Add(this.labelEmotivState);
            this.Controls.Add(this.buttonChat);
            this.Controls.Add(this.textBoxChat);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.labelDealter);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.listBoxDealer);
            this.Controls.Add(this.labelCurrentState);
            this.Controls.Add(this.buttonEvaluate);
            this.Controls.Add(this.labelTurn);
            this.Controls.Add(this.labelValue);
            this.Controls.Add(this.listBoxCards);
            this.Controls.Add(this.listBoxHistory);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.buttonJoin);
            this.Controls.Add(this.buttonStay);
            this.Controls.Add(this.buttonHit);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "Blackjack";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonHit;
        private System.Windows.Forms.Button buttonStay;
        private System.Windows.Forms.Button buttonJoin;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.ListBox listBoxHistory;
        private System.Windows.Forms.ListBox listBoxCards;
        private System.Windows.Forms.Label labelValue;
        private System.Windows.Forms.Label labelTurn;
        private System.Windows.Forms.Button buttonEvaluate;
        private System.Windows.Forms.Label labelCurrentState;
        private System.Windows.Forms.ListBox listBoxDealer;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label labelDealter;
        private System.Windows.Forms.TextBox textBoxChat;
        private System.Windows.Forms.Button buttonChat;
        private System.Windows.Forms.Label labelEmotivState;
    }
}

