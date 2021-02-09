import torch.nn as nn
import torch
import os

class VAE(nn.Module):
    def __init__(self, num_channals, latent_dim):
        super(VAE, self).__init__()
        self.num_channals = num_channals
        self.latent_dim = latent_dim
        # Define the architecture of VAE here
        # TODO START
        self.enc1 = nn.Sequential(nn.Conv2d(num_channals, 16, kernel_size=3, padding=1), nn.ReLU())
        self.enc2 = nn.Sequential(nn.Conv2d(16, 32, kernel_size=3, stride=2, padding=1), nn.ReLU())
        self.enc3 = nn.Sequential(nn.Conv2d(32, 32, kernel_size=3, padding=1), nn.ReLU())
        self.enc4 = nn.Sequential(nn.Conv2d(32, 16, kernel_size=3, stride=2, padding=1), nn.ReLU())
        self.enc5 = nn.Sequential(nn.Flatten(), nn.Linear(16 * 8 * 8, 2 * latent_dim), nn.ReLU())
        self.enc6 = nn.Linear(2 * latent_dim, 2 * latent_dim)
        self.dec1 = nn.Sequential(nn.Linear(latent_dim, latent_dim), nn.ReLU())
        self.dec2 = nn.Linear(latent_dim, 16 * 8 * 8)
        self.dec3 = nn.Sequential(nn.ConvTranspose2d(16, 32, kernel_size=3, stride=2, padding=1, output_padding=1),
                                  nn.ReLU())
        self.dec4 = nn.Sequential(nn.ConvTranspose2d(32, 32, kernel_size=3, padding=1), nn.ReLU())
        self.dec5 = nn.Sequential(nn.ConvTranspose2d(32, 16, kernel_size=3, stride=2, padding=1, output_padding=1),
                                  nn.ReLU())
        self.dec6 = nn.Sequential(nn.ConvTranspose2d(16, 1, kernel_size=3, padding=1), nn.Sigmoid())

        # TODO END

    def reparameterize(self, mu, log_var):
        '''
        *   Arguments:
            *   mu (torch.FloatTensor): [batch_size, latent_dim], parameters of the diagnoal Gaussian posterior q(z|x)
            *   log_var (torch.FloatTensor): [batch_size, latent_dim], parameters of the diagnoal Gaussian posterior q(z|x)
        *   Returns:
            *   reparameterized samples (torch.FloatTensor): [batch_size, latent_dim]
        '''
        # TODO START
        epsilon = torch.empty(mu.size()).normal_()
        sample_z = mu + (0.5 * log_var).exp() * epsilon
        return sample_z
        # TODO END

    def forward(self, x=None, z=None):
        '''
        *   Arguments:
            *   x (torch.FloatTensor): [batch_size, 1, 32, 32]
            *   z (torch.FloatTensor): [batch_size, latent_dim]
        *   Returns:
            *   if `x` is not `None`, return a list:
                *   Reconstruction of `x` (torch.FloatTensor)
                *   mu (torch.FloatTensor): [batch_size, latent_dim], parameters of the diagnoal Gaussian posterior q(z|x)
                *   log_var (torch.FloatTensor): [batch_size, latent_dim], parameters of the diagnoal Gaussian posterior q(z|x)
            *  if `x` is `None`, return samples generated from the given `z` (torch.FloatTensor): [num_samples, 1, 32, 32]
        '''
        if x is not None:
            # TODO START
            enc_x = self.enc1(x)
            enc_x = self.enc2(enc_x)
            enc_x = self.enc3(enc_x)
            enc_x = self.enc4(enc_x)
            enc_x = self.enc5(enc_x)
            enc_x = self.enc6(enc_x)
            mu, log_std = enc_x.split(self.latent_dim, dim=-1)
            log_var = 2 * log_std
            z = self.reparameterize(mu, log_var)
            recon_x = self.forward(None, z)  # sample
            return recon_x, mu, log_var
            # TODO END
        else:
            assert z is not None
            # TODO START
            gen_x = self.dec1(z)
            gen_x = self.dec2(gen_x)
            gen_x = gen_x.view(z.size()[0], 16, 8, 8)
            gen_x = self.dec3(gen_x)
            gen_x = self.dec4(gen_x)
            gen_x = self.dec5(gen_x)
            gen_x = self.dec6(gen_x)
            return gen_x
            # TODO END

    def restore(self, ckpt_dir):
        try:
            if os.path.exists(os.path.join(ckpt_dir, 'pytorch_model.bin')):
                path = os.path.join(ckpt_dir, 'pytorch_model.bin')
            else:
                path = os.path.join(ckpt_dir, str(max(int(name) for name in os.listdir(ckpt_dir))), 'pytorch_model.bin')
        except:
            return None
        self.load_state_dict(torch.load(path))
        return os.path.split(path)[0]

    def save(self, ckpt_dir, global_step):
        os.makedirs(os.path.join(ckpt_dir, str(global_step)), exist_ok=True)
        path = os.path.join(ckpt_dir, str(global_step), 'pytorch_model.bin')
        torch.save(self.state_dict(), path)
        return os.path.split(path)[0]
