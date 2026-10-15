FROM condaforge/miniforge3

ARG CONDA_ENV_NAME=sda
COPY environment.yml /tmp/environment.yml
RUN mamba env create -n $CONDA_ENV_NAME -f /tmp/environment.yml && conda clean -afy

ENV PATH=/opt/conda/envs/$CONDA_ENV_NAME/bin:$PATH
ENV CONDA_DEFAULT_ENV=$CONDA_ENV_NAME

RUN echo "conda activate $CONDA_ENV_NAME" >> ~/.bashrc
