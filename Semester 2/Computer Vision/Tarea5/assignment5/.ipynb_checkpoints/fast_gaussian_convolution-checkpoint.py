import numpy as np
from scipy import signal

def fast_gaussian_convolution(u,sigma):

	gaussian_kernel_1d_1 = np.expand_dims(signal.gaussian(u.shape[0],sigma),axis=1)	
	gaussian_kernel_1d_2 = np.expand_dims(signal.gaussian(u.shape[1],sigma),axis=1)
	gaussian_kernel_2d = np.matmul(gaussian_kernel_1d_1,np.transpose(gaussian_kernel_1d_2))
	gaussian_kernel_2d = gaussian_kernel_2d/np.sum(gaussian_kernel_2d)

	return np.real(np.fft.fftshift(np.fft.ifft2(np.fft.fft2(u)*np.fft.fft2(gaussian_kernel_2d))))